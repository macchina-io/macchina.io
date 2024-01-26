'use strict';

var bundleControllers = angular.module('bundlesControllers', []);

bundleControllers.controller('PageCtrl', ['$scope', '$rootScope', '$location', 'BundleService',
  function ($scope, $rootScope, $location, BundleService) {
    $scope.information = "";
    $scope.error = "";
    $scope.search = "";

    $scope.bundle = null;
    $scope.enableBundleUpgrade = false;

    $scope.allowedBundleActions = {
      start: false,
      stop: false,
      resolve: false,
      uninstall: false,
      upgrade: false
    };

    $scope.protectedBundles = [
    	'poco.net',
    	'osp.web'
    ];

    $scope.protectedBundlesHTTP = [
    	'osp.web.server'
    ];

    $scope.protectedBundlesHTTPS = [
    	'poco.crypto',
    	'poco.net.ssl',
    	'osp.web.server.secure'
    ];

    $scope.isActive = function(viewLocation) {
      return viewLocation === $location.path();
    };

    $scope.setAllowedBundleActions = function(state) {
      $scope.allowedBundleActions = {
        start: state == "resolved",
        stop: state == "active",
        resolve: state == "installed",
        uninstall: state != "active" && state != "uninstalled",
        upgrade: state != "active" && state != "uninstalled"
      };
    };

    $scope.setBundle = function(bundle) {
      $scope.bundle = bundle;
      if (bundle)
      {
        $scope.setAllowedBundleActions(bundle.state);
      }
      else
      {
        $scope.allowedBundleActions = {
          start: false,
          stop: false,
          resolve: false,
          uninstall: false,
          upgrade: false
        };
      }
    };

    $scope.setBundleState = function(state) {
      if ($scope.bundle)
      {
        $scope.bundle.state = state;
        $scope.setAllowedBundleActions(state);
      }
    };

    $scope.setError = function(msg) {
      $scope.error = msg;
    };

    $scope.setInformation = function(msg) {
      $scope.information = msg;
    };

    $scope.clearInformation = function() {
      $scope.information = "";
    };

    $scope.clearError = function() {
      $scope.error = "";
    };

    $scope.canStopBundle = function() {
      if (!$scope.bundle) return false;

      if ($scope.protectedBundles.indexOf($scope.bundle.symbolicName) > -1)
      	return false;

      if (location.protocol === 'https:')
      {
        if ($scope.protectedBundlesHTTPS.indexOf($scope.bundle.symbolicName) > -1)
          return false;
      }
      else
      {
        if ($scope.protectedBundlesHTTP.indexOf($scope.bundle.symbolicName) > -1)
          return false;
      }
      return true;
    };

    $scope.reloadBundle = function() {
      if ($scope.bundle)
      {
        $scope.$broadcast("reloadBundle");
      }
    };

    $scope.startBundle = function() {
      if ($scope.bundle)
      {
        BundleService.start($scope.bundle,
          function(state) {
            $scope.setBundleState(state);
          },
          function(error) {
            $scope.setError("Failed to start bundle: " + error);
          });
      }
    };

    $scope.stopBundle = function() {
      if ($scope.bundle)
      {
        if ($scope.bundle.requiredBy.length > 0)
        {
          $scope.showConfirmStop();
        }
        else
        {
          BundleService.stop($scope.bundle,
            function(state) {
              $scope.setBundleState(state);
            },
            function(error) {
              $scope.setError("Failed to stop bundle: " + error);
            });
        }
      }
    };

    $scope.confirmStop = function() {
      $scope.hideConfirmStop();
      if ($scope.bundle)
      {
        BundleService.stop($scope.bundle,
          function(state) {
            $scope.setBundleState(state);
          },
          function(error) {
            $scope.setError("Failed to stop bundle: " + error);
          });
      }
    };

    $scope.confirmStopAll = function() {
      $scope.hideConfirmStop();
      if ($scope.bundle)
      {
        BundleService.stopAll($scope.bundle,
          function(state) {
            $scope.setBundleState(state);
          },
          function(error) {
            $scope.setError("Failed to stop bundle: " + error);
          });
      }
    };

    $scope.cancelStop = function() {
      $scope.hideConfirmStop();
      return false;
    };

    $scope.resolveBundle = function() {
      if ($scope.bundle)
      {
        BundleService.resolve($scope.bundle,
          function(state) {
            $scope.setBundleState(state);
          },
          function(error) {
            $scope.setError("Failed to resolve bundle: " + error);
          });
      }
    };

    $scope.upgradeBundle = function() {
      $scope.enableBundleUpgrade = true;
    };

    $scope.upgradeBundleDone = function() {
      $scope.enableBundleUpgrade = false;
    };

    $scope.uninstallBundle = function() {
      if ($scope.bundle)
      {
        if (confirm("Uninstall bundle " + $scope.bundle.symbolicName + "?\nThis cannot be undone."))
        {
          BundleService.uninstall($scope.bundle,
            function(state) {
              $scope.setBundleState(state);
            },
            function(error) {
              $scope.setError("Failed to uninstall bundle: " + error);
            });
        }
      }
    };

    $scope.showConfirmStop = function() {
      $('#modalBackground').css('display', 'block');
      $('#confirmStop').css('display', 'block');
      $(document).on('keyup.confirmStop',
        function(e) {
          if (e.keyCode == 27)
          {
            $scope.hideConfirmStop();
          }
        }
      );
    };

    $scope.hideConfirmStop = function() {
    	$('#modalBackground').css('display', 'none');
    	$('#confirmStop').css('display', 'none');
    	$(document).unbind('keyup.confirmStop');
    };

    $rootScope.$on('$routeChangeStart', function(event, next, current) {
      $scope.clearError();
      $scope.clearInformation();
      $scope.enableBundleUpgrade = false;
    });
  }
]);

bundleControllers.controller('BundleListCtrl', ['$scope', '$http',
  function ($scope, $http) {
    $scope.setBundle(null);
    $scope.bundles = [];
    $scope.orderBy = "id";
    $scope.setOrderBy = function(col) {
      $scope.orderBy = col;
    }
    $http.get('/macchina/bundles/list.json').then(function(response) {
      $scope.bundles = response.data;
    });
  }
]);

bundleControllers.controller('BundleDetailCtrl', ['$scope', '$http', '$routeParams',
  function ($scope, $http, $routeParams) {
    $scope.bundles = [];

    $scope.loadBundle = function() {
      $http.get('/macchina/bundles/bundle.json?symbolicName=' + $routeParams.symbolicName).then(
        function(response) {
          $scope.bundle = response.data;
          $scope.setBundle($scope.bundle);
        }
      );
    };

    $scope.loadBundle();
    $scope.$on('reloadBundle',
      function(event) {
        $scope.loadBundle();
      }
    );
  }
]);

bundleControllers.controller('InstallCtrl', ['$scope', 'Upload',
  function($scope, Upload) {
    $scope.setBundle(null);

    $scope.status = "";

    $scope.$watch('files', function() {
      $scope.upload($scope.files);
    });

    $scope.upload = function(file) {
      if (file && file.size) {
        $scope.clearError();
        Upload.upload({
          url: '/macchina/bundles/actions.json',
          data: {
            action: 'install',
            file: file
          }
        }).then(
          function success(resp)
          {
            console.log(resp);
            $scope.status = "";
            if (resp.data.error == "")
            {
              window.location = "/macchina/bundles/#!/bundles/" + resp.data.symbolicName;
            }
            else
            {
              $scope.setError("Failed to install bundle: " + resp.data.error);
              $scope.reloadBundle();
            }
          },
          function error(resp) {
            $scope.status = "";
            $scope.setError("Failed to upload bundle file.");
            $scope.reloadBundle();  
          },
          function progress(evt)
          {
            var progressPercentage = parseInt(100.0 * evt.loaded / evt.total);
            if (progressPercentage < 100)
              $scope.status = "Uploading... (" + progressPercentage + "% )";
            else
              $scope.status = "Installing...";
          }
        );
      }
    };
  }
]);

bundleControllers.controller('UpgradeCtrl', ['$scope', 'Upload',
  function($scope, Upload) {
    $scope.status = "";

    $scope.$watch('files', function() {
      $scope.upload($scope.files);
    });

    $scope.upload = function(file) {
      if (file && file.size) {
        $scope.clearError();
        Upload.upload({
          url: '/macchina/bundles/actions.json',
          data: {
            action: 'upgrade',
            symbolicName: $scope.bundle.symbolicName,
            file: file
          },
        }).then(
          function success(resp)
          {
            $scope.status = "";
            $scope.reloadBundle();
            if (resp.data.error == "")
            {
              $scope.upgradeBundleDone();
            }
            else
            {
              $scope.setError("Failed to upgrade bundle: " + resp.data.error);
            }
          },
          function error(resp)
          {
            $scope.status = "";
            $scope.setError("Failed to upload bundle file.");
            $scope.reloadBundle();  
          },
          function progress(evt)
          {
            var progressPercentage = parseInt(100.0 * evt.loaded / evt.total);
            if (progressPercentage < 100)
              $scope.status = "Uploading... (" + progressPercentage + "% )";
            else
              $scope.status = "Upgrading...";
            }
        );
      }
    }
  }
]);

bundleControllers.controller('SessionCtrl', ['$scope', '$http',
  function($scope, $http) {
    $http.get('/macchina/session.json').then(
      function(response) {
        $scope.session = response.data;
        if (!response.data.authenticated)
        {
          window.location = "/";
        }
      }
    );
  }
]);

'use strict';

var bundleControllers = angular.module('bundlesControllers', []);

bundleControllers.controller('PageCtrl', ['$scope', '$rootScope', '$location', 'BundleService',
  function ($scope, $rootScope, $location, BundleService) {
    $scope.information = "";
    $scope.error = "";

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
    $http.get('/macchina/bundles/list.json').success(function(data) {
      $scope.bundles = data;
    });
  }
]);

bundleControllers.controller('BundleDetailCtrl', ['$scope', '$http', '$routeParams',
  function ($scope, $http, $routeParams) {
    $scope.bundles = [];

    $scope.loadBundle = function() {
      $http.get('/macchina/bundles/bundle.json?symbolicName=' + $routeParams.symbolicName).success(
        function(data) {
          $scope.bundle = data;
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

bundleControllers.controller('InstallCtrl', ['$scope', '$upload',
  function($scope, $upload) {
    $scope.setBundle(null);

    $scope.status = "";

    $scope.$watch('files', function() {
      $scope.upload($scope.files);
    });

    $scope.upload = function(files) {
      if (files && files.length) {
        $scope.clearError();
        var file = files[0];
        $upload.upload({
          url: '/macchina/bundles/actions.json',
          fields: {
            action: 'install'
          },
          file: file
        }).progress(function(evt) {
          var progressPercentage = parseInt(100.0 * evt.loaded / evt.total);
          if (progressPercentage < 100)
            $scope.status = "Uploading... (" + progressPercentage + "% )";
          else
            $scope.status = "Installing...";
        }).success(function(data, status, headers, config) {
          $scope.status = "";
          if (data.error == "")
          {
            window.location = "/macchina/bundles/#/bundles/" + data.symbolicName;
          }
          else
          {
            $scope.setError("Failed to install bundle: " + data.error);
            $scope.reloadBundle();
          }
        }).error(function() {
          $scope.status = "";
          $scope.setError("Failed to upload bundle file.");
          $scope.reloadBundle();
        });
      }
    };
  }
]);

bundleControllers.controller('UpgradeCtrl', ['$scope', '$upload',
  function($scope, $upload) {
    $scope.status = "";

    $scope.$watch('files', function() {
      $scope.upload($scope.files);
    });

    $scope.upload = function(files) {
      if (files && files.length) {
        $scope.clearError();
        var file = files[0];
        $upload.upload({
          url: '/macchina/bundles/actions.json',
          fields: {
            action: 'upgrade',
            symbolicName: $scope.bundle.symbolicName,
          },
          file: file
        }).progress(function(evt) {
          var progressPercentage = parseInt(100.0 * evt.loaded / evt.total);
          if (progressPercentage < 100)
            $scope.status = "Uploading... (" + progressPercentage + "% )";
          else
            $scope.status = "Upgrading...";
        }).success(function(data, status, headers, config) {
          $scope.status = "";
          $scope.reloadBundle();
          if (data.error == "")
          {
            $scope.upgradeBundleDone();
          }
          else
          {
            $scope.setError("Failed to upgrade bundle: " + data.error);
          }
        }).error(function() {
          $scope.status = "";
          $scope.setError("Failed to upload bundle file.");
          $scope.reloadBundle();
        });
      }
    };
  }
]);

bundleControllers.controller('SessionCtrl', ['$scope', '$http',
  function($scope, $http) {
    $http.get('/macchina/session.json').success(function(data) {
      $scope.session = data;
      if (!data.authenticated)
      {
        window.location = "/";
      }
    }
  );
  }
]);

'use strict';

var bundleControllers = angular.module('bundlesControllers', []);

bundleControllers.controller('PageCtrl', ['$scope', '$location', 'BundleService',
  function ($scope, $location, BundleService) {
    $scope.information = "";
    $scope.error = "";
    
    $scope.bundle = null;

    $scope.allowedBundleActions = {
      start: false,
      stop: false,
      resolve: false,
      uninstall: false
    };
    
    $scope.isActive = function(viewLocation) {
      return viewLocation === $location.path();
    };
    
    $scope.setAllowedBundleActions = function(state) {
      $scope.allowedBundleActions = {
        start: state == "resolved",
        stop: state == "active",
        resolve: state == "installed",
        uninstall: state != "active"
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
          uninstall: false
        };
      }
    };
    
    $scope.confirmInformation = function() {
      $scope.information = "";
    };
    
    $scope.confirmError = function() {
      $scope.error = "";
    };
    
    $scope.reloadBundle = function() {
      $scope.$broadcast("reloadBundle");
    };
    
    $scope.startBundle = function() {
      if ($scope.bundle)
      {
        BundleService.start($scope.bundle, null, null);
      }
    };

    $scope.stopBundle = function() {
      if ($scope.bundle)
      {
        var doStop = true;
        if ($scope.bundle.requiredBy.length > 0)
        {
          doStop = confirm("Other bundles depend on this bundle and will be stopped as well.\nStop bundle " + $scope.bundle.symbolicName + "?");
        }
        if (doStop)
        {
          BundleService.stop($scope.bundle, null, null);
        }
      }
    };

    $scope.resolveBundle = function() {
      if ($scope.bundle)
      {
        BundleService.resolve($scope.bundle, null, null);
      }
    };

    $scope.uninstallBundle = function() {
      if ($scope.bundle)
      {
        if (confirm("Uninstall bundle " + $scope.bundle.symbolicName + "?\nThis cannot be undone."))
        {
          BundleService.uninstall($scope.bundle, null, null);
        }
      }
    };  
  }
]);

bundleControllers.controller('BundleListCtrl', ['$scope', '$http',
  function ($scope, $http) {
    $scope.setBundle(null);
    $scope.bundles = [];
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

bundleControllers.controller('InstallCtrl', ['$scope',
  function($scope, $http) {
    $scope.setBundle(null);
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

'use strict';

var bundlesApp = angular.module('bundlesApp', [
  'ngRoute',
  'bundlesControllers',
  'bundlesServices'
]);

bundlesApp.config(['$routeProvider',
  function($routeProvider) {
    $routeProvider.
      when('/bundles', {
        templateUrl: '/macchina/bundles/templates/list.html',
        controller: 'BundleListCtrl'
      }).
      when('/bundles/:symbolicName', {
        templateUrl: '/macchina/bundles/templates/bundle.html',
        controller: 'BundleDetailCtrl'
      }).
      otherwise({
        redirectTo: '/bundles'
      });
  }]);

'use strict';

var bundlesApp = angular.module('bundlesApp', [
  'ngRoute',
  'ngFileUpload',
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
      when('/install', {
        templateUrl: '/macchina/bundles/templates/install.html',
        controller: 'InstallCtrl'
      }).
      otherwise({
        redirectTo: '/bundles'
      });
  }]);

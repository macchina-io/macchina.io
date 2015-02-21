'user strict';

var bundlesServices = angular.module('bundlesServices', []);

bundlesServices.service('BundleService', ['$http',
  function($http) {
    this.start = function(bundle, onsuccess, onfailure) {
      alert("start");
    };
    this.stop = function(bundle, onsuccess, onfailure) {
      alert("stop");
    };
    this.resolve = function(bundle, onsuccess, onfailure) {
      alert("resolve");
    };
    this.uninstall = function(bundle, onsuccess, onfailure) {
      alert("uninstall");
    };
  }
]);

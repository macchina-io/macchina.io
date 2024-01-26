'user strict';

var bundlesServices = angular.module('bundlesServices', []);

bundlesServices.service('BundleService', ['$http',
  function($http) {
    this.post = function(action, symbolicName, onsuccess, onfailure) {
      $http({
        method: "POST",
        url: "/macchina/bundles/actions.json",
        headers: {
          "Content-Type": "application/x-www-form-urlencoded"
        },
        transformRequest: function(obj) {
          var str = [];
          for (var p in obj) {
            str.push(encodeURIComponent(p) + "=" + encodeURIComponent(obj[p]));
          }
          return str.join("&");
        },
        data: {
          action: action,
          symbolicName: symbolicName
        }
      })
      .then(
        function(response) {
          if (response.data.error == "")
            onsuccess(response.data.bundleState);
          else
            onfailure(responsedata.error);
        },
        function() {
          onfailure("Server request failed.");
        }
      );
    };

    this.start = function(bundle, onsuccess, onfailure) {
      this.post("start", bundle.symbolicName, onsuccess, onfailure);
    };

    this.stop = function(bundle, onsuccess, onfailure) {
      this.post("stop", bundle.symbolicName, onsuccess, onfailure);
    };

    this.stopAll = function(bundle, onsuccess, onfailure) {
      this.post("stopAll", bundle.symbolicName, onsuccess, onfailure);
    };

    this.resolve = function(bundle, onsuccess, onfailure) {
      this.post("resolve", bundle.symbolicName, onsuccess, onfailure);
    };

    this.uninstall = function(bundle, onsuccess, onfailure) {
      this.post("uninstall", bundle.symbolicName, onsuccess, onfailure);
    };
  }
]);

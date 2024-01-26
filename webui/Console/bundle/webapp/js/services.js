'user strict';

var settingsServices = angular.module('consoleServices', []);

settingsServices.service('LogLevelService', ['$http',
  function($http) {
    this.load = function(onsuccess, onfailure) {
      $http({
        method: "GET", 
        url: "/macchina/console/loglevel"
      })
      .then(
        function success(response) {
          if (typeof response.data == "object")
            onsuccess(response.data);
          else
            onfailure(response.data.error);
        },
        function error() {
          onfailure("Server request failed.");
        }
      );
    };
    
    this.update = function(levels, onsuccess, onfailure) {
      $http({
        method: "PATCH", 
        url: "/macchina/console/loglevel",
        headers: {
          "Content-Type": "application/json"
        },
        data: levels
      })
      .then(
        function success(response) {
          if (!response.data.error)
            onsuccess(response.data);
          else
            onfailure(response.data.error);
        },
        function error() {
          onfailure("Server request failed.");
        }
      );
    };
  }
]);

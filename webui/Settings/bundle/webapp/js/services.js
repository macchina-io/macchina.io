'user strict';

var settingsServices = angular.module('settingsServices', []);

settingsServices.service('SettingsService', ['$http',
  function($http) {
    this.load = function(onsuccess, onfailure) {
      $http({
        method: "GET", 
        url: "/macchina/settings/properties.json"
      })
      .then(
        function(response) {
          if (typeof response.data == "object")
            onsuccess(response.data);
          else
            onfailure(response.data.error);
        },
        function() {
          onfailure("Server request failed.");
        }
      );
    };
    
    this.save = function(props, onsuccess, onfailure) {
      $http({
        method: "POST", 
        url: "/macchina/settings/properties.json",
        headers: {
          "Content-Type": "application/json"
        },
        data: props
      })
      .then(
        function(response) {
          if (!response.data.error)
            onsuccess(response.data);
          else
            onfailure(response.data.error);
        },
        function() {
          onfailure("Server request failed.");
        }
      );
    };
  }
]);

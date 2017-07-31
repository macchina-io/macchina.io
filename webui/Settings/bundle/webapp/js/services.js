'user strict';

var settingsServices = angular.module('settingsServices', []);

settingsServices.service('SettingsService', ['$http',
  function($http) {
    this.load = function(onsuccess, onfailure) {
      $http({
        method: "GET", 
        url: "/macchina/settings/properties.json"
      })
      .success(function(data) {
        if (typeof data == "object")
          onsuccess(data);
        else
          onfailure(data.error);
      })
      .error(function() {
        onfailure("Server request failed.");
      });
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
      .success(function(data) {
        if (!data.error)
          onsuccess(data);
        else
          onfailure(data.error);
      })
      .error(function() {
        onfailure("Server request failed.");
      });
    };
  }
]);

'user strict';

var playgroundServices = angular.module('playgroundServices', []);

playgroundServices.service('SandboxService', ['$http',
  function($http) {
    this.post = function(action, onsuccess, onfailure) {
      $http({
        method: "POST", 
        url: "/macchina/playground/" + action + ".json"
      })
      .success(function(data) {
        if (data.error == "")
          onsuccess(data.bundleState);
        else
          onfailure(data.error);
      })
      .error(function() {
        onfailure("Server request failed.");
      });
    };

    this.load = function(onsuccess, onfailure) {
      $http({
        method: "GET", 
        url: "/macchina/playground/load.json"
      })
      .success(function(data) {
        if (typeof data == "string")
          onsuccess(data);
        else
          onfailure(data.error);
      })
      .error(function() {
        onfailure("Server request failed.");
      });
    };
    
    this.save = function(script, onsuccess, onfailure) {
      $http({
        method: "POST", 
        url: "/macchina/playground/save.json",
        headers: {
          "Content-Type": "text/plain"
        },
        data: script
      })
      .success(function(data) {
        if (data.error == "")
          onsuccess(data.bundleState);
        else
          onfailure(data.error);
      })
      .error(function() {
        onfailure("Server request failed.");
      });
    };
    
    this.run = function(onsuccess, onfailure) {
      this.post("run", onsuccess, onfailure);
    };
    
    this.stop = function(onsuccess, onfailure) {
      this.post("stop", onsuccess, onfailure);
    };
    
    this.state = function(onsuccess, onfailure) {
      this.post("state", onsuccess, onfailure);
    };
  }
]);
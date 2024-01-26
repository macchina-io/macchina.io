'user strict';

var playgroundServices = angular.module('playgroundServices', []);

playgroundServices.service('SandboxService', ['$http',
  function($http) {
    this.post = function(action, onsuccess, onfailure) {
      $http({
        method: "POST", 
        url: "/macchina/playground/" + action + ".json"
      })
      .then(
        function(response) {
          if (response.data.error == "")
            onsuccess(response.data.bundleState);
          else
            onfailure(response.data.error);
        },
        function() {
          onfailure("Server request failed.");
        }
      );
    };

    this.load = function(onsuccess, onfailure) {
      $http({
        method: "GET", 
        url: "/macchina/playground/load"
      })
      .then(
        function(response) {
          if (typeof response.data == "string")
            onsuccess(response.data);
          else
            onfailure(response.data.error);
        },
        function() {
          onfailure("Server request failed.");
        }
      );
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
      .then(
        function(response) {
          if (response.data.error == "")
            onsuccess(response.data.bundleState);
          else
            onfailure(response.data.error);
        },
        function() {
          onfailure("Server request failed.");
        }
      );
    };
    
    this.run = function(onsuccess, onfailure) {
      this.post("run", onsuccess, onfailure);
    };

    this.restart = function(onsuccess, onfailure) {
      this.post("restart", onsuccess, onfailure);
    };
    
    this.stop = function(onsuccess, onfailure) {
      this.post("stop", onsuccess, onfailure);
    };
    
    this.state = function(onsuccess, onfailure) {
      this.post("state", onsuccess, onfailure);
    };

    this.info = function(onsuccess, onfailure) {
      $http({
        method: "GET", 
        url: "/macchina/playground/info.json"
      })
      .then(
        function(response) {
          if (response.data.error == "")
            onsuccess(response.data.bundleState, response.data.bundleInfo);
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
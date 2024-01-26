'user strict';

var deviceTreeServices = angular.module('deviceTreeServices', []);

deviceTreeServices.service('DeviceTreeService', ['$http',
  function($http) {
    this.load = function(onsuccess, onfailure) {
      $http({
        method: "GET", 
        url: "/macchina/devicetree/devicetree.jss"
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
  }
]);

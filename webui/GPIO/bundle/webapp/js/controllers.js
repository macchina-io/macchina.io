'use strict';

var gpioControllers = angular.module('gpioControllers', []);

gpioControllers.controller('GpioCtrl', ['$scope', '$http', '$interval',
    function($scope, $http, $interval) {
        $scope.devices = [];
        $scope.orderBy = "name";

        $scope.setOrderBy = function(col) {
            $scope.orderBy = col;
        }

        $scope.toggleState = function(id) {
            var jsonData = $.ajax({
                url: '/macchina/gpio/toggle.jss?gpio=' + encodeURIComponent(id),
                dataType: 'json',
            });
        }

        $http.get('/macchina/gpio/gpio.jss').success(function(data) {
            $scope.devices = data;
        });
        $interval(function() {
            $http.get('/macchina/gpio/gpio.jss').success(function(data) {
                $scope.devices = data;
            })
        }, 1000);
    }

]);

gpioControllers.controller('SessionCtrl', ['$scope', '$http',
    function($scope, $http) {
        $http.get('/macchina/session.json').success(function(data) {
            $scope.session = data;
            if (!data.authenticated) {
                window.location = "/";
            }
        });
    }
]);

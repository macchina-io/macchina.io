'use strict';

var sensorLogControllers = angular.module('sensorLogControllers', []);

var params = {};
var charts = {};
var since = 0;

sensorLogControllers.controller('sensorLogCtrl', ['$scope', '$http', '$interval', '$timeout',
  function($scope, $http, $interval, $timeout) {

    $scope.sensors = {
    };

    $scope.haveSensors = false;

    $scope.createChart = function(ctx, url, type, color, done) {
      var jsonData = $.ajax({
        url: url,
        dataType: 'json',
      }).done(function (results) {
        // Split timestamp and data into separate arrays
        var labels = [], data = [];
        results.forEach(function(packet) {
          labels.push(moment(packet.timestamp).format('HH:mm:ss'));
          data.push(packet.value);
          since = packet.timestamp;
        });

        var chart = new Chart(ctx, {
          type: 'line',
          data: {
            labels: labels,
            datasets: [{
              label:type,
              data: data,
              borderColor: color,
              pointBorderColor: color,
              pointBackgroundColor: 'rgba(255,255,255,1.0)',
              backgroundColor: tinycolor(color).setAlpha(0.3).toRgbString(),
              lineTension: 0,
              fill: true
            }]
          },
          options: {
            maintainAspectRatio: false
          }
        });
        done(chart)
      });
    }

    $scope.createSensorChart = function (index, id, unit, color) {
      var ctx = $('#chartCanvas_' + index)[0].getContext('2d');
      $scope.createChart(
      	ctx,
      	'/sensorlog/history.jss?sensor=' + encodeURIComponent(id),
      	unit,
      	color,
      	function(chart) {
      	  charts[id] = chart;
      	});
    }

    if (WebEvent.available)
    {
      WebEvent.onConnect = function() {
        WebEvent.subscribe('sensorlog');
      };

      WebEvent.onNotify = function(evt) {
        for (var id in $scope.sensors)
        {
          if ('sensorlog.' + id == evt.subject)
          {
          	$scope.sensors[id].value = parseFloat(evt.data);
          }
        }
        $scope.$apply();
      };

      WebEvent.connect();
    }

    Chart.defaults.global.legend.display = false;

    $http.get('/sensorlog/meta.jss').then(
      function(response) {
        $scope.sensors = response.data;
        for (var id in $scope.sensors)
        {
          $scope.haveSensors = true;
        }

        $http.get('/sensorlog/current.jss').then(
          function(response) {
            for (var id in response.data)
            {
	            $scope.sensors[id].value = response.data[id];
	          }
	        }
        );

        $http.get('/sensorlog/params.jss').then(
          function(response) {
            params = response.data;
            $timeout(function() {
              for (var id in $scope.sensors)
              {
                charts[id] = $scope.createSensorChart($scope.sensors[id].index, id, $scope.sensors[id].displayUnit, $scope.sensors[id].color);
              }
            }, 200);
            $interval(function() {
              function updateChartData(url, chart)
              {
                var jsonData = $.ajax({
                  url: url,
                  dataType: 'json',
                })
                .done(
                  function (results) {
                    for (var i = 0; i < results.length; i++)
                    {
                      var timestamp = results[i]['timestamp'];
                      var value = results[i]['value'];
                      var labels = chart.data.labels;
                      if (labels.length >= params.points) labels.shift();
                      labels.push(moment(timestamp).format('HH:mm:ss'));
                      var data = chart.data.datasets[0].data;
                      if (data.length >= params.points) data.shift();
                      data.push(value);
                      chart.update();
                      since = timestamp;
                    }
                 }
                );
              };
              for (var id in $scope.sensors)
              {
                updateChartData('/sensorlog/history.jss?sensor=' + encodeURIComponent(id) + '&since=' + since, charts[id]);
              }
           }, params.refresh);
          });
      }
    );
  }]);

sensorLogControllers.controller('SessionCtrl', ['$scope', '$http',
  function($scope, $http) {
    $http.get('/macchina/session.json').then(
      function(response) {
        $scope.session = response.data;
        if (!response.data.authenticated)
        {
          window.location = '/';
        }
      }
    );
  }]);

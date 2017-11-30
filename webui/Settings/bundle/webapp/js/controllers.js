'use strict';

var settingsControllers = angular.module('settingsControllers', []);

settingsControllers.controller('SettingsCtrl', ['$scope', 'SettingsService',
  function($scope, SettingsService) {
    $scope.data = [];
    $scope.error = "";
    $scope.selectedNodeName = "";
    $scope.selectedNode = null;
    $scope.idDOMOffset = 1e9;
    $scope.newNodeName = "";
    $scope.newNodeValue = null;
    $scope.nextId = 0;

    $scope.clearError = function() {
      $scope.error = "";
    };
    
    $scope.fullName = function(item) {
    	var result = "";
    	if (item && item.$modelValue)
    	{
    		result = item.$modelValue.title;
			while (item.$parentNodeScope && item.$parentNodeScope.$modelValue)
			{
				result = item.$parentNodeScope.$modelValue.title + "." + result;
				item = item.$parentNodeScope;
			}
		}
    	return result;
    }

    $scope.save = function() {
      $scope.clearError();
      var props = $scope.createJSONObject($scope.data);
      SettingsService.save(props,
        function(data) {
        },
        function(error) {
          $scope.error = error;
        }
      );
    };
  
    $scope.onNodeValueFocus = function(item) {
      $scope.clearSelection();
    }

    $scope.onNodeValueBlur = function(item) {
      if (item.$modelValue.value == "")
      {
        item.$modelValue.value = null;
      }
    }
  
    $scope.getNextId = function() {
      if ($scope.nextId == 0)
      {
        $scope.nextId = 1000;
      }
      else
      {
        $scope.nextId += 1;
      }
      return $scope.nextId;
    }
  
    $scope.showRenameNodePopup = function() 
    {
      $('#modalBackground').css("display", "block");
      $('#renameNodePopup').css("display", "block");
      $('#renameNodeForm input[name=name]').focus();
      $(document).on('keyup.renameNodePopup',
        function(e) {
          if (e.keyCode == 27) 
          {
            $scope.hideRenameNodePopup(); 
          }
          else if (e.keyCode == 13)
          {
            $scope.completeRenameNode();
            $scope.$apply();
          }
        }
      );   
    };

    $scope.hideRenameNodePopup = function() {
      $('#modalBackground').css("display", "none");
      $('#renameNodePopup').css("display", "none");
      $(document).unbind('keyup.renameNodePopup');
    };
  
    $scope.completeRenameNode = function() {
      if (!$scope.renameNodeForm.$valid) return;

      $scope.selectedNodeName = $scope.newNodeName;
      $scope.updateNodeName();
      $scope.hideRenameNodePopup();
    }
  
    $scope.renameNode = function(scope) {
      if (null == $scope.selectedNode)
      {
        alert("Please select a node to rename first.");
      }
      else
      {
        $scope.newNodeName = $scope.selectedNodeName;
        $scope.showRenameNodePopup();
      }
    }

    $scope.showDuplicateNodePopup = function() {
      $('#modalBackground').css("display", "block");
      $('#duplicateNodePopup').css("display", "block");
      $('#duplicateNodeForm input[name=name]').focus();
      $(document).on('keyup.duplicateNodePopup', 
        function(e) {
          if (e.keyCode == 27) 
          {
            $scope.hideDuplicateNodePopup(); 
          }
          else if (e.keyCode == 13)
          {
            $scope.completeDuplicateNode();
            $scope.$apply();
          }
        }
      );   
    };

    $scope.hideDuplicateNodePopup = function() {
      $('#modalBackground').css("display", "none");
      $('#duplicateNodePopup').css("display", "none");
      $(document).unbind('keyup.duplicateNodePopup');
    };
  
    $scope.completeDuplicateNode = function() {
      if (!$scope.duplicateNodeForm.$valid) return;

      var mv = $scope.selectedNode.$modelValue;
      var mvNew = angular.copy(mv);
      mvNew.title = $scope.newNodeName;
      increaseIds(mvNew, 0, 0);
    
      insertAsSibling($scope.data,mv,mvNew);

      $scope.clearSelection();
      $scope.hideDuplicateNodePopup();
    }
  
    $scope.duplicateNode = function(scope) {
      if (null==$scope.selectedNode)
      {
        alert("Please select a node to duplicate first.");
      }
      else
      {
        $scope.newNodeName = $scope.selectedNodeName + "-copy";
        $scope.showDuplicateNodePopup();
      }
    }
  
    $scope.showAddNodePopup = function() {
      $('#modalBackground').css("display", "block");
      $('#addNodePopup').css("display", "block");
      $('#addNodeForm input[name=name]').focus();
      $scope.newNodeName = "";
      $scope.newNodeValue = null;
      $(document).on('keyup.addNodePopup',
        function(e) {
          if (e.keyCode == 27) 
          {
            $scope.hideAddNodePopup(); 
          }
          else if (e.keyCode == 13)
          {
            $scope.completeAddNode();
            $scope.$apply();
          }
        }
      );   
    };

    $scope.hideAddNodePopup = function() {
      $('#modalBackground').css("display", "none");
      $('#addNodePopup').css("display", "none");
      $(document).unbind('keyup.addNodePopup');
    };

    $scope.completeAddNode = function() {
      if (!$scope.addNodeForm.$valid) return;
    
      if ($scope.newNodeValue != null && $scope.newNodeValue == "")
        $scope.newNodeValue = null;
    
      var nextId = $scope.getNextId();
      if ($scope.selectedNode != null)
      {
        $scope.selectedNode.$modelValue.nodes.push({
          id: nextId,
          title: $scope.newNodeName,
          value: $scope.newNodeValue,
          nodes: []
          });
        $scope.selectedNode.expand();
      }
      else
      {
        $scope.data.push({
          id: nextId,
          title: $scope.newNodeName,
          value: $scope.newNodeValue,
          nodes: []
        });
      }

      $scope.clearSelection();
      $scope.hideAddNodePopup();
    };
   
    $scope.addNode = function(item) {
      if (item)
      	$scope.selectNode(item);
      else
      	$scope.clearSelection();

      $scope.showAddNodePopup();
    };

    $scope.deleteNode = function(item) {
      if (null != item)
      {
        var ok = true;
        if (item.$modelValue.nodes != null && item.$modelValue.nodes.length > 0)
        {
          ok = confirm("Delete node \"" + item.$modelValue.title + "\" and all children?");
        }
        if (ok) 
        { 
          item.remove();
          $scope.clearSelection();
        }
      }
    };

    $scope.selectNode = function(item) {
      $scope.clearSelection();

      $scope.selectedNode = item;
      $scope.selectedNodeName = item.$modelValue.title;
      var idDOM = item.$modelValue.id + $scope.idDOMOffset;
      var el = document.getElementById(idDOM);
      el.attributes.class.value = el.attributes.class.value + " tree-node-selected";
    };
  
    $scope.clearSelection = function() {
      $(".tree-node").removeClass("tree-node-selected");
      $scope.selectedNode = null;
      $scope.selectedNodeName = null;
    }
 
    function increaseIds(item, parentId, index) {
      item.id = $scope.getNextId();

      if (null != item.nodes)
      {
        for (var i = 0; i < item.nodes.length; i++) 
        {
          increaseIds(item.nodes[i], item.id, i);
        }
      }
    }
  
    function adjustSiblingIDs(item, id, index) {
      item.id = $scope.getNextId();

      if (null != item.nodes)
      {
        for (var i = 0; i < item.nodes.length; i++) 
        {
          adjustSiblingIDs(item.nodes[i], item.id, i);
        }
      }
    }
  
    function insertAsSibling(arr, item, itemNew) {
      var index = arr.indexOf(item);
    
      if (index >= 0)
      {
        adjustSiblingIDs(itemNew, item.id, -1);
        arr.splice(index + 1, 0, itemNew);
        return true;
      }
      else
      {
        for (var i=0; i < arr.length; i++) 
        {
          if (null != arr[i].nodes)
          {
            if (insertAsSibling(arr[i].nodes, item, itemNew))
              return true;
          }
        }
      }
    
      return false;
    }
    
    $scope.addNodeValue = function(node) {
      node.$modelValue.value = "";
    }
  
    $scope.updateNodeName = function() {
      $scope.selectedNode.$modelValue.title = $scope.selectedNodeName;
    };
  
    $scope.toggleNode = function(item) {
      item.toggle();
    };

    $scope.collapseAll = function() {
      $scope.$broadcast('angular-ui-tree:collapse-all');
    };

    $scope.expandAll = function() {
      $scope.$broadcast('angular-ui-tree:expand-all');
    };
  
    $scope.createJSONObject = function(obj)
    {
      if (null == obj) return null;
    
      var objRet = {};
    
      if (obj.length != 0)
      {
        for (var i = 0; i < obj.length; i++)
        {
          var propname = obj[i].title;
      
          if (null != obj[i].nodes && obj[i].nodes.length > 0)
          {
            objRet[propname] = $scope.createJSONObject(obj[i].nodes);
          }
          else if (null != obj[i].value)
          {
            objRet[propname] = obj[i].value;
          }
        }
      }
      else
      {
        var propname = obj.title;
      
        if (null != obj.nodes)
        {
          var ret = ($scope.createJSONObject(obj.nodes));
          if (null != ret)
          {
            objRet[propname] = ret;
          }
        }
        else if (null != obj.value)
        {
          objRet[propname] = obj.value;
        }
      }

      return objRet;
    }
  
    $scope.createDataArray = function(obj)
    {
      var arr = [];
    
      for (var x in obj) 
      {
        var node = { 
          id: $scope.getNextId(), 
          title: x, 
          value: null, 
          nodes: [] 
        };

        if (typeof obj[x] === "object" )
        {
          node.nodes = $scope.createDataArray(obj[x]);
        }
        else
        {
          node.value = obj[x];
        }

        arr.push(node);
      }

      return arr;
    };
    
    SettingsService.load(
      function(props) {
        $scope.data = $scope.createDataArray(props);
        $scope.collapseAll();
      },
      function(error) {
        $scope.error = error;
      }
    );

  }
]);

settingsControllers.controller('SessionCtrl', ['$scope', '$http',
  function($scope, $http) {
    $http.get('/macchina/session.json').success(function(data) {
      $scope.session = data;
      if (!data.authenticated)
      {
        window.location = "/";
      }
    });
  }
]);

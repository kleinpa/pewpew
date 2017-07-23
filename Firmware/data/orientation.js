angular
  .module('pewpew', [])
  .controller('PewPewController', ['$scope', '$http', '$window', function($scope, $http, $window) {
    $scope.r = .5;
    $scope.i = .5;
    $scope.p = 1;
    tries = 0;
    (function update() {
      $http({
        url: '/set',
        method: "GET",
        params: {r:$scope.r, i:$scope.i, p:$scope.p*255},
        timeout: 1000}).
      then(function success() {
        $scope.status = 'connected';
        setTimeout(update, 10);
      }, function error() {
        tries++;
        if(tries < 2)
          $scope.status = 'connecting';
        else {
          $scope.state = {};
          $scope.status = 'disconnected';
        }
        setTimeout(update, 10);
      });
    })();
    $scope.p = 255;
    angular.element($window).bind("deviceorientation", function(event) {
      $scope.r = ((event.alpha+90)%180)-90;
      $scope.i = ((event.beta+90)%180)-90;
      $scope.changed = true;
      $scope.$apply();
    });
  }]);

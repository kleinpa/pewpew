angular
  .module('pewpew', [])
  .controller('PewPewController', ['$scope', '$http', '$document', function($scope, $http, $document) {
    $scope.r = .5;
    $scope.i = .5;
    $scope.p = 0;
    tries = 0;
    (function update() {
      $http({
          url: '/set',
        method: "GET",
        params: {r:-$scope.r*180+90, i:-$scope.i*180+90, p:$scope.p*255},
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

    $scope.move = function(event) {
      $scope.r = event.clientX / event.target.clientWidth;
      $scope.i = event.clientY / event.target.clientHeight;
      $scope.p = event.buttons & 1;
      $scope.changed = true;
    };
    var ar, ai, br, bi, cr, ci, dr, di;
    $scope.keypress = function(event) {
      switch(event.charCode) {
      case 49: //1
        ar = $scope.r;
        ai = $scope.i;
        break;
      case 50: //1
        br = $scope.r;
        bi = $scope.i;
        break;
      case 51: //1
        cr = $scope.r;
        ci = $scope.i;
        break;
      case 52: //1
        dr = $scope.r;
        di = $scope.i;
        break;
      case 53: //1
        $scope.r = ar;
        $scope.i = ai;
        $scope.p = 1;
        break;
      case 54: //1
        $scope.r = br;
        $scope.i = bi;
        $scope.p = 1;
        break;
      case 55: //1
        $scope.r = cr;
        $scope.i = ci;
        $scope.p = 1;
        break;
      case 56: //1
        $scope.r = dr;
        $scope.i = di;
        $scope.p = 1;
        break;
      }
    };
  }]);

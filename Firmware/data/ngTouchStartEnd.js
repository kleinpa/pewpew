// From https://github.com/nglar/ngTouch/blob/master/ngTouch.js

"use strict";

angular.module("ngTouchStartEnd", [])
.directive("ngTouchstart", function ($parse) {
  return function (scope, element, attr) {
      element.bind('touchstart', onTouchStart);

      function onTouchStart(event) {
        $parse(attr.ngTouchstart)(scope)
      };
    };
})
.directive("ngTouchend", function ($parse) {
  return function (scope, element, attr) {
      element.bind('touchend', onTouchEnd);

      function onTouchEnd(event) {
        $parse(attr.ngTouchend)(scope)
      };
    };
});

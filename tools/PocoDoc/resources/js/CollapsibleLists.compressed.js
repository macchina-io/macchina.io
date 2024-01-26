/*

CollapsibleLists.js

An object allowing lists to dynamically expand and collapse

Created by Stephen Morley - http://code.stephenmorley.org/ - and released under
the terms of the CC0 1.0 Universal legal code:

http://creativecommons.org/publicdomain/zero/1.0/legalcode

Modified by Guenter Obiltschnig (added expansion via URI query string)

*/

var CollapsibleLists=new function(){function e(e){for(var a=e.getElementsByTagName("ul"),l=0;l<a.length;l++){for(var t=a[l];"LI"!=t.nodeName;)t=t.parentNode;t==e&&(a[l].style.display="block")}e.className=e.className.replace(/(^| )collapsibleList(Open|Closed)( |$)/,""),a.length>0&&(e.className+=" collapsibleList"+(open?"Open":"Closed"))}function a(e){return function(a){a||(a=window.event);for(var t=a.target?a.target:a.srcElement;"LI"!=t.nodeName;)t=t.parentNode;t==e&&l(e)}}function l(e){for(var a=e.className.match(/(^| )collapsibleListClosed( |$)/),l=e.getElementsByTagName("ul"),t=0;t<l.length;t++){for(var n=l[t];"LI"!=n.nodeName;)n=n.parentNode;n==e&&(l[t].style.display=a?"block":"none")}e.className=e.className.replace(/(^| )collapsibleList(Open|Closed)( |$)/,""),l.length>0&&(e.className+=" collapsibleList"+(a?"Open":"Closed"))}function t(e){var a=RegExp("[\\?&]"+(e=e.replace(/[\[]/,"\\[").replace(/[\]]/,"\\]"))+"=([^&#]*)").exec(location.search);return null===a?"":decodeURIComponent(a[1].replace(/\+/g," "))}this.apply=function(a){for(var l=document.getElementsByTagName("ul"),n=0;n<l.length;n++){if(l[n].className.match(/(^| )collapsibleList( |$)/)&&(this.applyTo(l[n],!0),!a))for(var s=l[n].getElementsByTagName("ul"),o=0;o<s.length;o++)s[o].className+=" collapsibleList";var c=t("expand");if(c){var r=document.getElementById(c);r&&e(r)}}},this.applyTo=function(e,t){for(var n=e.getElementsByTagName("li"),s=0;s<n.length;s++)t&&e!=n[s].parentNode||(n[s].addEventListener?n[s].addEventListener("mousedown",function(e){e.preventDefault()},!1):n[s].attachEvent("onselectstart",function(){event.returnValue=!1}),n[s].addEventListener?n[s].addEventListener("click",a(n[s]),!1):n[s].attachEvent("onclick",a(n[s])),l(n[s]))},this.expand=function(a){e(a)}};
/*
 * Poor man's auto reload. Use with these bookmarklets:
 *
 * javascript:(function () {localStorage.setItem('shouldAutoReload', 'true'); window.location.reload()})()
 * javascript:(function () {localStorage.setItem('shouldAutoReload', 'false')})()
 */
document.addEventListener("DOMContentLoaded", function(event) {
  const shouldAutoReload = localStorage.getItem('shouldAutoReload');
  if ('true' == shouldAutoReload) {
    window.setTimeout(function () {window.location.reload()}, 4*1000);
  }
});

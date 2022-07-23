R"(
var contextPanel = $.GetContextPanel();
var hudRadar = contextPanel.FindChildTraverse('HudRadar');

var dashboardLabel = hudRadar.FindChildTraverse('DashboardLabel');
dashboardLabel.style.backgroundImgOpacity = '${alpha}'; 
)"
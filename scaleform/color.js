R"(
var contextPanel = $.GetContextPanel();
var hudRadar = contextPanel.FindChildTraverse('HudRadar');

var roundBorder = hudRadar.FindChildTraverse('Radar__Round--Border');
roundBorder.style.borderRadius = '50% / 50%';
roundBorder.style.borderWidth = '2px';
roundBorder.style.borderStyle = 'solid';
roundBorder.style.borderColor = `${radarColor}`;
roundBorder.style.opacity = '0.50';

var squareBorder = hudRadar.FindChildTraverse('Radar__Square--Border');
squareBorder.style.borderRadius = '0';
squareBorder.style.borderWidth = '2px';
squareBorder.style.borderStyle = 'solid';
squareBorder.style.borderColor = `${radarColor}`;
squareBorder.style.opacity = '0.50';

var dashboardLabel = hudRadar.FindChildTraverse('DashboardLabel');
dashboardLabel.style.color = `${dashboardLabelColor}`;
)"
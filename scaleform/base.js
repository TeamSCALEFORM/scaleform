R"(
var contextPanel = $.GetContextPanel();

var hudBottomLeftImg = "https://images2.imgbox.com/ac/02/og3P1Xvp_o.png"
var moneyBgImg = "https://images2.imgbox.com/a9/2f/lt6Pj1Mc_o.png"
var dashboardLabelImg = "https://images2.imgbox.com/62/17/y3tvD95I_o.png"
var hudTeamCountBgT = "https://images2.imgbox.com/0f/d5/fpNsbsSC_o.png";
var hudTeamCountBgCT = "https://images2.imgbox.com/05/8f/f32nMOYd_o.png";

var hudBottomLeft = contextPanel.FindChildTraverse('HudWeaponPanel').FindChildTraverse('WeaponPanelBottomBG');
hudBottomLeft.style.backgroundImage = `url(${hudBottomLeftImg})`;	
hudBottomLeft.style.backgroundColor = '#00000000';
hudBottomLeft.style.backgroundSize = '100% 100%';
hudBottomLeft.style.width = '312px';
hudBottomLeft.style.height = '59px';
hudBottomLeft.style.marginLeft = '37px';
hudBottomLeft.style.marginTop = '-6px';
hudBottomLeft.style.transform = 'translateX(-1px)';
hudBottomLeft.style.overflow = 'noclip';
hudBottomLeft.style.backgroundImgOpacity = '0.95';

var hudMoney = contextPanel.FindChildTraverse('HudMoney');
// Background position is 0% by default which doesn't show
// our own buy cart. This is handled in {buyzone.js}
var moneyBg = hudMoney.FindChildTraverse('MoneyBG');
moneyBg.style.width = '291px';
moneyBg.style.height = '44px';
moneyBg.style.horizontalAlign = 'center';
moneyBg.style.verticalAlign = 'center';
moneyBg.style.marginLeft = '0px';
moneyBg.style.backgroundImage = `url(${moneyBgImg})`;
moneyBg.style.backgroundColor = '#00000000';
moneyBg.style.backgroundSize = '200% 100%';
moneyBg.style.backgroundRepeat = 'no-repeat';
moneyBg.style.backgroundImgOpacity = '0.95';

for (var moneyText of hudMoney.FindChildrenWithClassTraverse('money-text')) {
    moneyText.style.horizontalAlign = 'left';
    moneyText.style.flowChildren = 'right';
    moneyText.style.verticalAlign = 'middle';
    moneyText.style.marginLeft = '0px';
}

for (var moneyLabel of hudMoney.FindChildrenWithClassTraverse('money-text-label')) {
	moneyLabel.style.marginTop = '3px';
	moneyLabel.style.marginLeft = '65px';
	moneyLabel.style.transform = 'translateX(0px)';    
}

// Fully remove this, as due to layouting rules we have to replace this with
// a dynamically UV-mapped image
for (var buyIcon of hudMoney.FindChildrenWithClassTraverse('money-text-buy-icon')) {
	buyIcon.style.visibility = 'collapse';
}

// Reposition and change the color of animations
var moneyAdd = hudMoney.FindChildTraverse('Money-Add');
moneyAdd.style.color = '#7CC213';
moneyAdd.style.marginLeft = '25px';
var moneyAddFlash = hudMoney.FindChildTraverse('Money-AddFlash');
moneyAddFlash.style.color = '#D3E798';
var moneyRemove = hudMoney.FindChildTraverse('Money-Remove');
moneyRemove.style.marginLeft = '30px';
moneyRemove.style.color = '#FD2424';

// Radar
var hudRadar = contextPanel.FindChildTraverse('HudRadar');

// Alpha is handled in {alpha.js}
var dashboardLabel = contextPanel.FindChildTraverse('DashboardLabel');
dashboardLabel.style.horizontalAlign = 'center';
dashboardLabel.style.verticalAlign = 'center';
dashboardLabel.style.marginLeft = '0px';
dashboardLabel.style.marginTop = '-14px';
dashboardLabel.style.paddingTop = '10px';
dashboardLabel.style.width = '280px';
dashboardLabel.style.height = '51px';
dashboardLabel.style.paddingLeft = '12px';
dashboardLabel.style.backgroundImage = `url(${dashboardLabelImg})`;
dashboardLabel.style.backgroundColor = '#00000000';
dashboardLabel.style.backgroundSize = '100% 100%';
dashboardLabel.style.fontFamily = 'Stratum2';
dashboardLabel.style.fontWeight = 'bold';
dashboardLabel.style.fontSize = '26px';
dashboardLabel.style.letterSpacing = '-0.3px';

// Teamcount (only score style)
var hudTeamCounter = context_panel.FindChildTraverse('HudTeamCounter');
hudTeamCounter.style.height = '100%';
var aliveTextT = hudTeamCounter.FindChildTraverse('AliveTextT');
var aliveTextCT = hudTeamCounter.FindChildTraverse('AliveTextCT');
aliveTextT.style.fontSize = '13px';
aliveTextT.style.fontWeight ='normal';
aliveTextCT.style.fontWeight = 'normal';
aliveTextCT.style.fontSize = '13px';
aliveTextCT.style.letterSpacing = '0px';
aliveTextT.style.letterSpacing = '0px';
aliveTextCT.style.marginBottom = '-2px';
aliveTextT.style.marginBottom = '-2px';
aliveTextT.style.textShadow = '2px 1px 1px 0.0 #000000';
aliveTextCT.style.textShadow = '2px 1px 1px 0.0 #000000';
aliveTextT.style.fontFamily = 'Stratum2';
aliveTextCT.style.fontFamily = 'Stratum2';
aliveTextT.style.color = '#e6e6e680';
aliveTextCT.style.color = '#e6e6e680';
var winsT = hudTeamCounter.FindChildTraverse('ScoreT');
var winsCT = hudTeamCounter.FindChildTraverse('ScoreCT');
winsT.style.fontFamily = 'Stratum2 Bold Monodigit';
winsCT.style.fontFamily = 'Stratum2 Bold Monodigit';
winsT.style.color = '#A38B60C8';
winsCT.style.color = '#5C7F8AC8';
var timer = hudTeamCounter.FindChildTraverse('TimerText');
timer.style.fontFamily = 'Stratum2 Bold Monodigit';
timer.style.marginTop = '-2px';
timer.style.fontSize = '28px';
for (var tAlive of context_panel.FindChildTraverse('HudTeamCounter').FindChildrenWithClassTraverse('TeamCounter__AliveT')){
    tAlive.style.backgroundImage = `url(${hudTeamCountBgT})`;   
}
for (var ctAlive of context_panel.FindChildTraverse('HudTeamCounter').FindChildrenWithClassTraverse('TeamCounter__AliveCT'))
{
    ctAlive.style.backgroundImage = `url(${hudTeamCountBgCT})`;   
}
for (var scoreText of context_panel.FindChildTraverse('HudTeamCounter').FindChildrenWithClassTraverse('TeamCounter__AliveCount'))
{
    scoreText.style.color = '#ffffff';
}

var historyText = context_panel.FindChildTraverse('HudChat').FindChildTraverse('ChatHistoryText');
historyText.style.fontFamily = 'Stratum2';
historyText.style.fontSize = '18px';
historyText.style.fontWeight = 'lighter';
historyText.style.letterSpacing = '0px';
historyText.style.backgroundColor = '#000000CC';

var textEntry = context_panel.FindChildTraverse('HudChat').FindChildTraverse('ChatTextEntryBox');
textEntry.style.fontFamily = 'Stratum2';
textEntry.style.fontSize = '18px';
textEntry.style.fontWeight = 'lighter';
textEntry.style.letterSpacing = '0px';

var sendChat = context_panel.FindChildTraverse('HudChat').FindChildTraverse('ChatSendButton');
sendChat.style.fontFamily = 'Stratum2';
sendChat.style.fontSize = '18px';
sendChat.style.fontWeight = 'lighter';
sendChat.style.letterSpacing = '0px';

for(var sentChat of context_panel.FindChildrenWithClassTraverse('AlertText'))
{
     sentChat.style.backgroundColor = 'gradient( linear, 100% 0%, 0% 0%, from( #00000000 ), color-stop( 0.7, #00000077 ), to( #00000077 ) )';
     sentChat.style.textShadow = '1px 1px 2px #00000055';
     sentChat.style.fontFamily = 'Stratum2';
     sentChat.style.fontWeight = 'normal';
     sentChat.style.fontSize = '21.5px';
     sentChat.style.letterSpacing = '.43px';
     sentChat.style.paddingLeft = '28px';
     sentChat.style.paddingBottom = '0px';
}

)"
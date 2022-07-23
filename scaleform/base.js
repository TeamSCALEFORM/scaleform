R"(
var contextPanel = $.GetContextPanel();

var hudBottomLeftImg = "https://images2.imgbox.com/ac/02/og3P1Xvp_o.png"
var moneyBgImg = "https://images2.imgbox.com/a9/2f/lt6Pj1Mc_o.png"

var hudBottomLeft = contextPanel.FindChildTraverse('HudWeaponPanel').FindChildTraverse('WeaponPanelBottomBG');
hudBottomLeft.backgroundImage = `url(${hudBottomLeftImg})`;	
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

for (var moneyText of hud_money.FindChildrenWithClassTraverse('money-text')) {
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
moneyAdd.marginLeft = '25px';
var moneyAddFlash = hudMoney.FindChildTraverse('Money-AddFlash');
moneyAddFlash.style.color = '#D3E798';
var moneyRemove = hudMoney.FindChildTraverse('Money-Remove');
moneyRemove.marginLeft = '30px';
moneyRemove.style.color = '#FD2424';
)"
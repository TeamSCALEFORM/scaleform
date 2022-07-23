R"(
var contextPanel = $.GetContextPanel();
var hudMoney = contextPanel.FindChildTraverse('HudMoney');
var moneyBg = hudMoney.FindChildTraverse('MoneyBG');
moneyBg.style.backgroundPosition = '${buyZone}';
)"
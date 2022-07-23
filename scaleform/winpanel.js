R"(
if (${pendingMvp})
{
    var context_panel = $.GetContextPanel();
    var textColor = ${isCt} ? '#B4BBBE' : '#D6C8B5';
    var winpanelBackground = ${isCt} ? 'https://images2.imgbox.com/9b/a5/igisaPg8_o.png' : ${isT} ? 'https://images2.imgbox.com/c9/be/43gnCOjE_o.png' : 'https://images2.imgbox.com/9b/a5/igisaPg8_o.png';
    if (${is2013})
        winpanelBackground = ${isCt} ? 'https://images2.imgbox.com/77/d5/T79ImP9g_o.png' : ${isT} ? 'https://images2.imgbox.com/26/56/eEUIVB7m_o.png' : 'https://images2.imgbox.com/77/d5/T79ImP9g_o.png';

    for (var mvp of context_panel.FindChildTraverse('HudWinPanel').FindChildrenWithClassTraverse('MVP'))
    {
        mvp.style.visibility = 'visible';
        mvp.style.width = '815px';
    }

    for (var winpanelBG of context_panel.FindChildTraverse('HudWinPanel').FindChildrenWithClassTraverse('TeamBG__MainBG')) {
        winpanelBG.style.marginTop = '-42px';
        winpanelBG.style.width = '815px';
        winpanelBG.style.height = '155px';
        winpanelBG.style.backgroundImage = `url(${winpanelBackground})`;
        winpanelBG.style.backgroundSize = 'cover';
        winpanelBG.style.marginLeft = '105px';
    }

    for (var teamTitle of context_panel.FindChildTraverse('HudWinPanel').FindChildrenWithClassTraverse('TeamFG__Title'))
    {
       teamTitle.style.visibility = ${is2013} ? 'collapse' : 'visible';
       teamTitle.style.marginTop = '-45px';
       teamTitle.style.color = textColor;
       teamTitle.style.fontSize = '40px';
    }

    for (var star of context_panel.FindChildTraverse('HudWinPanel').FindChildrenWithClassTraverse('MVP__WinnerStar')){
        star.style.visibility = ${is2013} ? 'collapse' : 'visible';
        star.style.marginTop = "25%";
        star.style.marginLeft = "-2px";
        star.SetImage('https://cdn.discordapp.com/attachments/954389817536421908/957676079642980392/star.svg');
        star.style.transform = 'translateY(5px)';
    }

    for (var playerName of context_panel.FindChildTraverse('HudWinPanel').FindChildrenWithClassTraverse('MVP__WinnerName')){
        playerName.style.visibility = 'visible';
        playerName.style.marginTop = ${is2013} ? "15px" : "20px";
        playerName.style.color = ${isCt} ? "#717377" : "#8A7E6C";
        playerName.style.marginLeft = ${is2013} ? "-4px" : "2px";
        playerName.style.fontSize = ${is2013 ? "22px" : "17px";
        playerName.style.fontWeight = ${is2013} ? 'light' : 'bold';
        playerName.style.transform = 'translateY(5px)';
    }
    for (var profileImg of context_panel.FindChildTraverse('HudWinPanel').FindChildrenWithClassTraverse('MVP__Avatar'))
    {
        if{${is2013}}
        {
            profileImg.style.visibility = 'visible';
            profileImg.style.zIndex = "500";
            profileImg.style.height = "59px";
            profileImg.style.width = "59px";
            profileImg.style.marginTop = "19px";
            profileImg.style.padding = '0px';
            profileImg.style.paddingTop = '2px';
            profileImg.style.backgroundSize = '50%';
            profileImg.style.marginLeft = "25px";
            profileImg.style.backgroundColor = 'gradient( linear, 0% 0%, 0% 100%, from( #7d7d7d ), to( #202020) )';
            for(var imgPadding of context_panel.FindChildTraverse('HudWinPanel').FindChildrenWithClassTraverse('AvatarImage'))
            {
                imgPadding.style.padding = '0px';
            }
        }
        else
        {
            profileImg.style.visibility = 'visible';
            profileImg.style.zIndex = "1000";
            profileImg.style.height = "60px";
            profileImg.style.width = "60px";
            profileImg.style.backgroundColor = "#00000000";
            profileImg.style.marginTop = "19px";
            profileImg.style.paddingLeft = "0px";
            profileImg.style.marginLeft = "25px";
        }
    }
    var funfact = context_panel.FindChildTraverse('FunFactText');
    if{!${is2013}}
    {
        ff.style.width = '813px';
        ff.style.x = '107px';
        ff.style.marginTop = '5px';
        ff.style.backgroundColor = '#000000CC';
    }
    else
    {
        funfact.style.width = '813px';
        funfact.style.height = '40px';
        funfact.style.x = '107px';
        funfact.style.marginTop = '5px';
        funfact.style.backgroundColor = '#000000CC';
        funfact.style.textAlign = 'left';
        funfact.style.fontSize = '19px';
        funfact.style.fontWeight = 'light';
        funfact.style.verticalAlign = 'center';
        funfact.style.paddingTop = '10px';
        funfact.style.paddingLeft = '25px';
    }

    /* <--------- REMOVALS ---------->*/
    for (var h of context_panel.FindChildTraverse('HudWinPanel').FindChildrenWithClassTraverse('TeamBG__hrTop')) {h.style.x = '0';h.style.y = '0';h.style.width = '0';h.style.height = '0';}
    for (var h of context_panel.FindChildTraverse('HudWinPanel').FindChildrenWithClassTraverse('TeamBG__hrMid')) {h.style.x = '0';h.style.y = '0';h.style.width = '0';h.style.height = '0';}
	for (var h of context_panel.FindChildTraverse('HudWinPanel').FindChildrenWithClassTraverse('TeamBG__hrBot')) {h.style.x = '0';h.style.y = '0';h.style.width = '0';h.style.height = '0';}
    for (var hideTeamIcon of context_panel.FindChildTraverse('HudWinPanel').FindChildrenWithClassTraverse('TeamBG__DefaultLogo')){hideTeamIcon.style.visibility = 'collapse'; hideTeamIcon.style.opacity = '0';}
    

}
)"
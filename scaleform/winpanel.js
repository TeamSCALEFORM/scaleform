R"(
if (${pendingMvp})
{
    var context_panel = $.GetContextPanel();
    var winpanelBackground = "https://images2.imgbox.com/9b/a5/igisaPg8_o.png";
    for (var hideTeamIcon of context_panel.FindChildTraverse('HudWinPanel').FindChildrenWithClassTraverse('TeamBG__DefaultLogo')){hideTeamIcon.style.visibility = 'collapse'; hideTeamIcon.style.opacity = '0';}
    for(var wpbg of context_panel.FindChildTraverse('HudWinPanel').FindChildrenWithClassTraverse('TeamBG__MainBG'))
    {
        for (var title of context_panel.FindChildTraverse('HudWinPanel').FindChildrenWithClassTraverse('TeamFG__Title'))
        {
            var textColor = "#FFFFFF";
            title.style.fontSize = "40px";
            title.style.marginTop = "-45px";
            if(${isCT})
            {
                textColor = "#B4BBBE";
                if(${is2018})
                {
                    title.style.visibility = 'visible';
                    winpanelBackground = "https://images2.imgbox.com/9b/a5/igisaPg8_o.png";
                    for (var img of context_panel.FindChildTraverse('HudWinPanel').FindChildrenWithClassTraverse('MVP__Avatar'))
                    {
                        img.style.visibility = 'visible';
                        img.style.zIndex = "1000";
                        img.style.height = "60px";
                        img.style.width = "60px";
                        img.style.backgroundColor = "#00000000";
                        img.style.marginTop = "19px";
                        img.style.paddingLeft = "0px";
                        img.style.marginLeft = "25px";
                    }
                    for (var star of context_panel.FindChildTraverse('HudWinPanel').FindChildrenWithClassTraverse('MVP__WinnerStar')){
                        star.style.visibility= "visible";
                        star.style.marginTop = "25%";
                        star.style.marginLeft = "-2px";
                        star.SetImage('https://cdn.discordapp.com/attachments/954389817536421908/957676079642980392/star.svg');
                        star.style.transform = 'translateY(5px)';
                    }
                    for (var playerName of context_panel.FindChildTraverse('HudWinPanel').FindChildrenWithClassTraverse('MVP__WinnerName')){
                        playerName.style.visibility = 'visible';
                        playerName.style.marginTop = "20px";
                        playerName.style.color = "#717377";
                        playerName.style.marginLeft = "2px";
                        playerName.style.fontSize = "17px";
                        playerName.style.fontWeight = 'bold';
                        playerName.style.transform = 'translateY(5px)';
                    }
                    var ff = hwp.FindChildTraverse('FunFactText');
                    ff.style.width = '813px';
                    ff.style.x = '107px';
                    ff.style.marginTop = '5px';
                    ff.style.backgroundColor = '#000000CC';
                }
                if(${is2013})
                {
                    title.style.visibility = 'collapse';
                    winpanelBackground = "https://images2.imgbox.com/77/d5/T79ImP9g_o.png";
                    for (var img of context_panel.FindChildTraverse('HudWinPanel').FindChildrenWithClassTraverse('MVP__Avatar'))
                    {
                       img.style.visibility = 'visible';
                        img.style.zIndex = "500";
                        img.style.height = "59px";
                        img.style.width = "59px";
                        img.style.marginTop = "19px";
                        img.style.padding = '0px';
                        img.style.paddingTop = '2px';
                        img.style.backgroundSize = '50%';
                        img.style.marginLeft = "25px";
                        img.style.backgroundColor = 'gradient( linear, 0% 0%, 0% 100%, from( #7d7d7d ), to( #202020) )';  
                    }
                    for (var star of context_panel.FindChildTraverse('HudWinPanel').FindChildrenWithClassTraverse('MVP__WinnerStar'))
                    { star.style.visibility= 'collapse'; }
                    for (var playerName of context_panel.FindChildTraverse('HudWinPanel').FindChildrenWithClassTraverse('MVP__WinnerName'))
                    {
                        playerName.style.visibility = 'visible';
                        playerName.style.marginTop = "15px";
                        playerName.style.color = "#717377";
                        playerName.style.marginLeft = "-4px";
                        playerName.style.fontSize = "22px";
                        playerName.style.fontWeight = 'light';
                        playerName.style.transform = 'translateY(5px)';
                    }
                    var ff = context_panel.FindChildTraverse('FunFactText');
                    ff.style.width = '813px';
                    ff.style.height = '40px';
                    ff.style.x = '107px';
                    ff.style.marginTop = '5px';
                    ff.style.backgroundColor = '#000000CC';
                    ff.style.textAlign = 'left';
                    ff.style.fontSize = '19px';
                    ff.style.fontWeight = 'light';
                    ff.style.verticalAlign = 'center';
                    ff.style.paddingTop = '10px';
                    ff.style.paddingLeft = '25px';
                }
            }

            if(${isT})
            {
                textColor = "#D6C8B5";
                if(${is2018})
                {
                    winpanelBackground = "https://images2.imgbox.com/c9/be/43gnCOjE_o.png";
                    title.style.visibility = 'visible';
                    for (var img of context_panel.FindChildTraverse('HudWinPanel').FindChildrenWithClassTraverse('MVP__Avatar'))
                    {
                       img.style.visibility = 'visible';
                        img.style.zIndex = "1000";
                        img.style.height = "60px";
                        img.style.width = "60px";
                        img.style.backgroundColor = "#00000000";
                        img.style.marginTop = "19px";
                        img.style.paddingLeft = "0px";
                        img.style.marginLeft = "25px";
                    }
                    for (var star of context_panel.FindChildTraverse('HudWinPanel').FindChildrenWithClassTraverse('MVP__WinnerStar')){
                        star.style.visibility= "visible";
                        star.style.marginTop = "25%";
                        star.style.marginLeft = "-2px";
                        star.SetImage('https://cdn.discordapp.com/attachments/954389817536421908/957676079642980392/star.svg');
                        star.style.transform = 'translateY(5px)';
                    }
                    for (var playerName of context_panel.FindChildTraverse('HudWinPanel').FindChildrenWithClassTraverse('MVP__WinnerName')){
                        playerName.style.visibility = 'visible';
                        playerName.style.marginTop = "20px";
                        playerName.style.color = "#717377";
                        playerName.style.marginLeft = "2px";
                        playerName.style.fontSize = "17px";
                        playerName.style.fontWeight = 'bold';
                        playerName.style.transform = 'translateY(5px)';
                    }
                    var ff = hwp.FindChildTraverse('FunFactText');
                    ff.style.width = '813px';
                    ff.style.x = '107px';
                    ff.style.marginTop = '5px';
                    ff.style.backgroundColor = '#000000CC';
                }
                if(${is2013})
                {
                    winpanelBackground = "https://images2.imgbox.com/26/56/eEUIVB7m_o.png";
                    title.style.visibility = 'collapse';
                    for (var img of context_panel.FindChildTraverse('HudWinPanel').FindChildrenWithClassTraverse('MVP__Avatar'))
                    {
                       img.style.visibility = 'visible';
                        img.style.zIndex = "500";
                        img.style.height = "59px";
                        img.style.width = "59px";
                        img.style.marginTop = "19px";
                        img.style.padding = '0px';
                        img.style.paddingTop = '2px';
                        img.style.backgroundSize = '50%';
                        img.style.marginLeft = "25px";
                        img.style.backgroundColor = 'gradient( linear, 0% 0%, 0% 100%, from( #7d7d7d ), to( #202020) )';  
                    }
                    for (var star of context_panel.FindChildTraverse('HudWinPanel').FindChildrenWithClassTraverse('MVP__WinnerStar'))
                    { star.style.visibility= 'collapse'; }
                    for (var playerName of context_panel.FindChildTraverse('HudWinPanel').FindChildrenWithClassTraverse('MVP__WinnerName'))
                    {
                        playerName.style.visibility = 'visible';
                        playerName.style.marginTop = "15px";
                        playerName.style.color = "#717377";
                        playerName.style.marginLeft = "-4px";
                        playerName.style.fontSize = "22px";
                        playerName.style.fontWeight = 'light';
                        playerName.style.transform = 'translateY(5px)';
                    }
                    var ff = context_panel.FindChildTraverse('FunFactText');
                    ff.style.width = '813px';
                    ff.style.height = '40px';
                    ff.style.x = '107px';
                    ff.style.marginTop = '5px';
                    ff.style.backgroundColor = '#000000CC';
                    ff.style.textAlign = 'left';
                    ff.style.fontSize = '19px';
                    ff.style.fontWeight = 'light';
                    ff.style.verticalAlign = 'center';
                    ff.style.paddingTop = '10px';
                    ff.style.paddingLeft = '25px';
                }
            }

            if(!${isT} && !${isCT}) // draw
            {

            }
            title.style.color = `${textColor}`;
        }
        wpbg.style.backgroundImage = `url(${winpanelBackground})`;
        wpbg.style.backgroundSize = 'cover';
        wpbg.style.width = '815px';
        wpbg.style.height = '155px';
        wpbg.style.marginTop = '-42px';
        wpbg.style.marginLeft = '105px';
    }
    for (var mvp of context_panel.FindChildTraverse('HudWinPanel').FindChildrenWithClassTraverse('MVP'))
    {
        mvp.style.visibility = 'visible';
        mvp.style.width = "815px";
    }
}
)"
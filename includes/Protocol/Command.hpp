//
// Command.hpp for pfa in /home/gautier/Projets/pfa
// 
// Made by gautier lefebvre
// Login   <lefebv_n@epitech.net>
// 
// Started on  Fri Jan 10 16:52:11 2014 gautier lefebvre
// Last update Wed Mar 26 11:06:14 2014 Gautier Lefebvre
//

#ifndef		__PROTOCOL_COMMAND_HPP__
#define		__PROTOCOL_COMMAND_HPP__

#include	<string>

namespace	Command {
  enum		Command {
    ERR = -1,
    EXIT,		// pour quitter le thread reseau
    CO,			// connexion
    REG,		// inscription
    PINFOS,		// player infos
    PSTATS,		// player stats
    SETSTATUS,		// set status
    SETRACE,		// set race
    AFD,		// add friend
    DFD,		// delete friend
    AIFD,		// answer invitation friend
    SWH,		// send whisp
    SMSGGLB,		// send msg global (chat ig)
    RMSGGLB,		// recv msg global (chat ig)
    SMSGGRP,		// send msg group
    NFD,		// new friend
    LFD,		// lose friend
    SFD,		// friend status
    APIG,		// Ajoute player dans group
    AGR,		// answer group request
    KPG,		// Kick player group
    LVGP,		// Leave group
    DELGRP,		// delete group
    GR,			// Group request
    NPIG,		// New player in group
    PLG,		// Player left group
    GPLD,		// leader du group
    GRPKICKED,		// you were kicked
    GRPDELETED,		// group deleted
    GRPMBRCHGRACE,	// groupe member changed race
    RWH,		// rcv whisp
    RMSGGRP,		// recv msg group
    SUCCESS,		// success command
    FAIL,		// fail command
    QUICKLAUNCH,	// lance partie rapide
    LEAVEGAMESEARCH,	// quitte la recherche de partie
    GAMESEARCHING,	// en recherche de partie
    ENDGAMESEARCHING,	// fin de recherche de partie
    GAMELOADING,	// chargement partie
    GAMELAUNCH,		// lancement partie
    PLAYERINROOM,	// joueur dans la room
    PLAYERREADY,	// joueur pret
    IAMREADY,		// joueur pret
    GAMEREADY,		// player ready
    FINFOS,		// fichier infos
    ASKFILEEXISTS,	// demande si le fichier existe
    FILEEXISTS,		// réponse ASKFILEEXISTS
    FILECHUNK,		// partie de fichier
    JOINSPECTATOR,	// join game as spectator
    LEAVESPECTATOR,	// leave specto
    OCREATE,		// Create Item
    ODESTROY,		// Destroy Item
    OMAJ,		// Update Item
    OWP,		// Item Waypoint
    OSTOP,		// Stop item Action
    OACT,		// Item Action
    OGRPMOVE,		// Move un groupe d'item
    PING,		// Ping sur la map
    USTANCE,		// Changement de la stance d'une unité
    UCHGSTANCE,		// Demande de changement de la stance d'une unité
    UCHGGRPSTANCE,	// Demande de changement de la stance d'un groupe d'unité
    UASKSTANCE,		// Demande la stance d'une unité
    OASKINFO,		// Demande des informations sur une unité
    OASKMOVE,		// Demande de déplacement d'un item
    DAYNIGHT,		// Indique le changement Jour/Nuit
    ASKDAYNIGHT,	// Demande si c'est le jour ou la nuit
    PRESS,		// Donne les ressources d'un joueur
    ASKPRESS,		// Demande les ressources d'un joueur
    OMOVE,		// Annonce qu'un item bouge
    OASKACT,		// Demande l'action d'un item
    OASKACTCAPA,	// Demande à activer une capacité
    UBUILD,		// Unité construit un bâtiment
    UASKPROD,		// Demande production unité
    UPROD,		// Mise en production d'une unité
    NEWFRIENDREQUEST,	// New friend request
    REMOVEFRIENDREQUEST, // Del friend request
    OACTCAPA,		// Annonce si une capacité est activée ou non
    UPURESS,		// Une unité transporte des ressources
    ASKUPURESS,		// Demande les ressources transportées par une unité
    ASKOEFFECT,		// Demande les effets appliqués à un item
    OSTOPEFFECT,	// Annonce la fin d'un effet appliqué à un item
    OEFFECT,		// Annonce qu'un effet est appliqué à un item
    OEFFECTS,		// Donne les effets appliqués à un item
    BPRODF,		// Une unité a été produite
    OSETACTION,		// Demande à assigner une action à un item
    OSETACTIONS,	// Demande à assigner une action à plusieurs items
    UASKDPROD,		// Demande à retirer une unité de la production
    UDPROD,		// Retire une unité de la lsite de production
    HPUOBJ,		// Un héro a ramassé un objet
    ASKHOBJ,		// Demande les objets que possède un héro
    HPUOBJS,		// Donne les objets possédés par un héro
    HROBJ,		// Un héro a laché un objet
    ASKHPUOBJ,		// Demande à un héro de ramasser un objet
    ASKHROBJ,		// Demande à un héro de poser un objet
    PAMELIO,		// Donne une amélioration d'un joueur
    PPRODAMELIO,	// Un joueur vient juste de produire une amélioration
    ASKPAMELIO,		// Demande les améliorations d'un joueur
    ASKPRODAMELIO,	// Demande à produire une amélioration
    ASKDAMELIO,		// Demande à retirer une amélioration de la liste de production
    DAMELIO,		// Une amélioration a été retirée de la liste de production
    PRODAMELIO,		// Annonce la mise en production d'une amélioration
    ASKPSAMELIO,	// Demande les améliorations d'un type d'unité
    UASKBUILD,		// Demande à une unité d'aller aider à bâtir un bâtiment
    USTOPBUILD,		// Une unité arrête de construire un bâtiment
    BBUILT,		// Un bâtiment vient d'être construit
    UHARVEST,		// Une unité récolte
    UDEPOSIT,		// Une unité dépose des ressources dans un batiment
    UASKHARVEST,	// Demande à une unité d'aller récolter
    USASKHARVEST,	// Demande à plusieurs unités d'aller récolter
    ASKRESSSPOTID,	// Demande des infos sur un spot de ressources
    RESSSPOT,		// Donne des infos sur un spot de ressources
    UPDSPOT,		// Mise à jour d'un spot
    UWAITHARVEST,	// Une unité attends pour récolter
    USTOPWAITHARVEST,	// Une unité a fini d'attendre pour récolter
    USTOPHARVEST,	// Une unité a fini de récolter
    OTMPEFFECT,		// Une unité subit un effet qui ne vient pas d'elle
    OSTOPTMPEFFECT,	// Une unité ne subit plus un effet qui ne vient pas d'elle
    OASKAUTOCAPA,	// Demande qu'un item change l'état automatique d'une capacité
    USASKBUILD,		// Demande qu'un groupe aille construire un bâtiment
    OATTACK,		// Un item attaque un autre item
    ASKOATTACK,		// Demande qu'un item attaque un autre item
    OUSECAP,		// Une item utilise une capacité
    ASKOUSECAP,		// Demande qu'un item utilise une capacité
    ASKUPATROL,		// Demande à une unité de patrouiller
    ASKUSPATROL,	// Demande à des unités de patrouiller
    ASKOSATTACK,	// Demande à plusieurs items d'attaquer d'autres items
    ASKOZONEATTACK,	// Demande à un item d'attaquer une zone
    ASKOSZONEATTACK,	// Demande à plusieurs items d'attaquer une zone
    OZONEATTACK,	// Indique qu'un item attaque une zone
    ASKOUSEZONECAP,	// Demande à un item d'utiliser une capacité de zone
    OUSEZONECAP,	// Un item utilise une capacité de zone
    OUSECAPA,		// Un item utilise une capacité
    PLAYER,		// Annonce les joueurs lors d'une partie
    YOUARE,		// Annonce qui est le joueur
    ASKCBUILDING	// Demande à créer un batiment
    //    UPATROL		// Annonce qu'une unité est en train de patrouiller
  };

  const std::string	CommandToString(::Command::Command c);

  struct	CommandString {
    ::Command::Command	command;
    std::string		string;
  };

  static const int	NB_COMMAND = 129;

  static const CommandString CommandStringTab[::Command::NB_COMMAND]={
    {Command::ERR, "ERR"},
    {Command::EXIT, "EXIT"},
    {Command::CO, "CO"},
    {Command::REG, "REG"},
    {Command::PINFOS, "PINFOS"},
    {Command::PSTATS, "PSTATS"},
    {Command::SETSTATUS, "SETSTATUS"},
    {Command::SETRACE, "SETRACE"},
    {Command::AFD, "AFD"},
    {Command::DFD, "DFD"},
    {Command::AIFD, "AIFD"},
    {Command::SWH, "SWH"},
    {Command::SMSGGRP, "SMSGGRP"},
    {Command::RMSGGLB, "RMSGGLB"},
    {Command::SMSGGLB, "SMSGGLB"},
    {Command::NFD, "NFD"},
    {Command::LFD, "LFD"},
    {Command::SFD, "SFD"},
    {Command::APIG, "APIG"},
    {Command::AGR, "AGR"},
    {Command::KPG, "KPG"},
    {Command::LVGP, "LVGP"},
    {Command::DELGRP, "DELGRP"},
    {Command::GR, "GR"},
    {Command::NPIG, "NPIG"},
    {Command::PLG, "PLG"},
    {Command::GPLD, "GPLD"},
    {Command::GRPKICKED, "GRPKICKED"},
    {Command::GRPDELETED, "GRPDELETED"},
    {Command::GRPMBRCHGRACE, "GRPMBRCHGRACE"},
    {Command::RWH, "RWH"},
    {Command::RMSGGRP, "RMSGGRP"},
    {Command::SUCCESS, "SUCCESS"},
    {Command::FAIL, "FAIL"},
    {Command::QUICKLAUNCH, "QUICKLAUNCH"},
    {Command::LEAVEGAMESEARCH, "LEAVEGAMESEARCH"},
    {Command::GAMESEARCHING, "GAMESEARCHING"},
    {Command::ENDGAMESEARCHING, "ENDGAMESEARCHING"},
    {Command::GAMELOADING, "GAMELOADING"},
    {Command::FINFOS, "FINFOS"},
    {Command::ASKFILEEXISTS, "ASKFILEEXISTS"},
    {Command::FILEEXISTS, "FILEEXISTS"},
    {Command::FILECHUNK, "FILECHUNK"},
    {Command::IAMREADY, "IAMREADY"},
    {Command::PLAYERREADY, "PLAYERREADY"},
    {Command::OCREATE, "OCREATE"},
    {Command::ODESTROY, "ODESTROY"},
    {Command::OMAJ, "OMAJ"},
    {Command::OWP, "OWP"},
    {Command::OSTOP, "OSTOP"},
    {Command::OACT, "OACT"},
    {Command::OGRPMOVE, "OGRPMOVE"},
    {Command::PING, "PING"},
    {Command::USTANCE, "USTANCE"},
    {Command::UCHGSTANCE, "UCHGSTANCE"},
    {Command::UCHGGRPSTANCE, "UCHGGRPSTANCE"},
    {Command::UASKSTANCE, "UASKSTANCE"},
    {Command::OASKINFO, "OASKINFO"},
    {Command::OASKMOVE, "OASKMOVE"},
    {Command::DAYNIGHT, "DAYNIGHT"},
    {Command::ASKDAYNIGHT, "ASKDAYNIGHT"},
    {Command::PRESS, "PRESS"},
    {Command::ASKPRESS, "ASKPRESS"},
    {Command::OMOVE, "OMOVE"},
    {Command::OASKACT, "OASKACT"},
    {Command::OASKACTCAPA, "OASKACTCAPA"},
    {Command::UBUILD, "UBUILD"},
    {Command::UASKPROD, "UASKPROD"},
    {Command::UPROD, "UPROD"},
    {Command::NEWFRIENDREQUEST, "NEWFRIENDREQUEST"},
    {Command::OACTCAPA, "OACTCAPA"},
    {Command::UPURESS, "UPURESS"},
    {Command::ASKUPURESS, "ASKUPURESS"},
    {Command::ASKOEFFECT, "ASKOEFFECT"},
    {Command::OSTOPEFFECT, "OSTOPEFFECT"},
    {Command::OEFFECT, "OEFFECT"},
    {Command::OEFFECTS, "OEFFECTS"},
    {Command::BPRODF, "BPRODF"},
    {Command::OSETACTION, "OSETACTION"},
    {Command::OSETACTIONS, "OSETACTIONS"},
    {Command::UASKDPROD, "UASKDPROD"},
    {Command::UDPROD, "UDPROD"},
    {Command::HPUOBJ, "HPUOBJ"},
    {Command::ASKHOBJ, "ASKHOBJ"},
    {Command::HPUOBJS, "HPUOBJS"},
    {Command::HROBJ, "HROBJ"},
    {Command::ASKHPUOBJ, "ASKHPUOBJ"},
    {Command::ASKHROBJ, "ASKHROBJ"},
    {Command::PAMELIO, "PAMELIO"},
    {Command::PPRODAMELIO, "PPRODAMELIO"},
    {Command::ASKPAMELIO, "ASKPAMELIO"},
    {Command::ASKPRODAMELIO, "ASKPRODAMELIO"},
    {Command::ASKDAMELIO, "ASKDAMELIO"},
    {Command::DAMELIO, "DAMELIO"},
    {Command::PRODAMELIO, "PRODAMELIO"},
    {Command::ASKPSAMELIO, "ASKPSAMELIO"},
    {Command::UASKBUILD, "UASKBUILD"},
    {Command::USTOPBUILD, "USTOPBUILD"},
    {Command::BBUILT, "BBUILT"},
    {Command::UHARVEST, "UHARVEST"},
    {Command::UDEPOSIT, "UDEPOSIT"},
    {Command::UASKHARVEST, "UASKHARVEST"},
    {Command::USASKHARVEST, "USASKHARVEST"},
    {Command::ASKRESSSPOTID, "ASKRESSSPOTID"},
    {Command::RESSSPOT, "RESSSPOT"},
    {Command::UPDSPOT, "UPDSPOT"},
    {Command::UWAITHARVEST, "UWAITHARVEST"},
    {Command::USTOPWAITHARVEST, "USTOPWAITHARVEST"},
    {Command::USTOPHARVEST, "USTOPHARVEST"},
    {Command::OTMPEFFECT, "OTMPEFFECT"},
    {Command::OSTOPTMPEFFECT, "OSTOPTMPEFFECT"},
    {Command::OASKAUTOCAPA, "OASKAUTOCAPA"},
    {Command::USASKBUILD, "USASKBUILD"},
    {Command::OATTACK, "OATTACK"},
    {Command::ASKOATTACK, "ASKOATTACK"},
    {Command::OUSECAP, "OUSECAP"},
    {Command::ASKOUSECAP, "ASKOUSECAP"},
    {Command::ASKUPATROL, "ASKUPATROL"},
    {Command::ASKUSPATROL, "ASKUSPATROL"},
    {Command::ASKOSATTACK, "ASKOSATTACK"},
    {Command::ASKOZONEATTACK, "ASKOZONEATTACK"},
    {Command::ASKOSZONEATTACK, "ASKOSZONEATTACK"},
    {Command::OZONEATTACK, "OZONEATTACK"},
    {Command::ASKOUSEZONECAP, "ASKOUSEZONECAP"},
    {Command::OUSEZONECAP, "OUSEZONECAP"},
    {Command::OUSECAP, "OUSECAP"},
    {Command::PLAYER, "PLAYER"},
    {Command::YOUARE, "YOUARE"},
    {Command::ASKCBUILDING, "ASKCBUILDING"}
    //    {Command::UPATROL, "UPATROL"}
  };
}

#endif

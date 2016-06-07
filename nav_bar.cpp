#include <Wt/WApplication>
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WLineEdit>
#include <Wt/WMenu>
#include <Wt/WMessageBox>
#include <Wt/WNavigationBar>
#include <Wt/WPopupMenu>
#include <Wt/WPopupMenuItem>
#include <Wt/WStackedWidget>
#include <Wt/WTemplate>
#include <Wt/WText>
#include <Wt/WTextArea>
#include <Wt/WTabWidget>
#include <Wt/WImage>
#include <Wt/WBootstrapTheme>
#include <Wt/WHBoxLayout>
#include <Wt/WVBoxLayout>
#include <Wt/WPanel>

#include <boost/algorithm/string.hpp>

#include "nav_bar.h"
#include "SpartanProfile.h"
#include "PlaylistRanksContainer.h"
#include "RecentMatchesContainer.h"

Wt::WContainerWidget *nav_bar()
{
    // Main Container holding navbar and content
    Wt::WContainerWidget *container = new Wt::WContainerWidget();
    
    // Content stack shows content, one at a time
    Wt::WStackedWidget *contentsStack = new Wt::WStackedWidget(container);
    contentsStack->addStyleClass("container");
    
    // Container holding content for layout purposes
    Wt::WContainerWidget *container2 = new Wt::WContainerWidget();
    
    // Create a NAVBAR
    Wt::WNavigationBar *navigation = new Wt::WNavigationBar(container);
    navigation->setTitle("Halo Viewer",
                         "http://haloviewer.bluewizard.ca/");
    navigation->setResponsive(true);
    navigation->addStyleClass("navbar-fixed-top");
    navigation->addStyleClass("navbar-inner");
    
    // Setup a Left-aligned menu.
    Wt::WMenu *leftMenu = new Wt::WMenu(contentsStack, container2);
    navigation->addMenu(leftMenu, Wt::AlignCenter);
    
    Wt::WText *searchResult = new Wt::WText("Buy or Sell... Bye!");
    
    // Create Spartan profile
    SpartanProfile *mySpartan = new SpartanProfile();
    
    // Create Profile view container
    Wt::WContainerWidget *profile = new Wt::WContainerWidget();
    profile->addStyleClass("summary-container");
    
    
    // User summary template (emblem, name, rank etc.)
    Wt::WTemplate *t = new Wt::WTemplate("<div class=\"summary-container\">\n<img src=\"${emblem-url}\" class=\"emblem-image\" />\n<div class=\"spartan-name\">${spartan-name}</div>\n<div class=\"spartan-rank\">SR ${spartan-rank}</div>\n</div>");
    std::string emblem_url("https://image.halocdn.com/h5/emblems/311_0_31_48?width=256&hash=%2blRdfGUDXqlSen9Z1eRb8OoX%2fqYz9zaLqu3TNgYxffs%3d");
    boost::replace_all(emblem_url, "&", "&amp;");
    t->bindString("emblem-url", emblem_url);
    t->bindWidget("spartan-name", new Wt::WText("CLWakaLaka"));
    t->bindWidget("spartan-rank", new Wt::WText("SR 74"));
    profile->addWidget(t);
    
    // Ranks Container shows playlist ranks for a given SpartanProfile
    Wt::WContainerWidget *summary_layout = new Wt::WContainerWidget();
    PlaylistRanksContainer *ranks = new PlaylistRanksContainer(mySpartan);
    
    Wt::WContainerWidget *panels = new Wt::WContainerWidget();
    panels->setWidth("60%");
    Wt::WPanel *panel = new Wt::WPanel();
    panel->setTitle("Collapsible panel");
    panel->addStyleClass("centered-example");
    panel->setCollapsible(true);
    Wt::WAnimation animation(Wt::WAnimation::SlideInFromTop,
                             Wt::WAnimation::EaseOut,
                             100);
    panel->setAnimation(animation);
    Wt::WText *temp_text = new Wt::WText(mySpartan->printRecentMatches());
    panel->setCentralWidget(temp_text);
    panels->addWidget(panel);
    
    RecentMatchesContainer *recent_matches_panel = new RecentMatchesContainer(mySpartan);
    
    ranks->setFloatSide(Wt::Left);
    recent_matches_panel->setFloatSide(Wt::Left);
    summary_layout->addWidget(ranks);
    summary_layout->addWidget(recent_matches_panel);
    
    
    // Create TabWidget for profile view
    Wt::WTabWidget *tabW = new Wt::WTabWidget(profile);
    Wt::WTextArea *text = new Wt::WTextArea(mySpartan->getRanks());
    tabW->addTab(summary_layout,
                 "Summary", Wt::WTabWidget::PreLoading);
    tabW->addTab(text,
                 "Weapons", Wt::WTabWidget::PreLoading);
    tabW->addTab(new Wt::WTextArea("You could change any other style attribute of the"
                                   " tab widget by modifying the style class."
                                   " The style class 'trhead' is applied to this tab."),
                 "Medals", Wt::WTabWidget::PreLoading)->setStyleClass("trhead");
    tabW->setStyleClass("tabwidget");
    
    // Add containers to Left Menu
    leftMenu->addItem("Profile", profile);
    leftMenu->addItem("Matches", new Wt::WText("Layout contents"));
    leftMenu->addItem("Sales", searchResult);
    
    // Setup a Right-aligned menu.
    Wt::WMenu *rightMenu = new Wt::WMenu();
    navigation->addMenu(rightMenu, Wt::AlignRight);
    
    // Create a popup submenu for the Help menu.
    Wt::WPopupMenu *popup = new Wt::WPopupMenu();
    popup->addItem("Contents");
    popup->addItem("Index");
    popup->addSeparator();
    popup->addItem("About");
    
    panel->expanded().connect(std::bind([=] () {
        temp_text->setText(mySpartan->printRecentMatches());
    }));
    
    popup->itemSelected().connect(std::bind([=] (Wt::WMenuItem *item) {
        Wt::WMessageBox *messageBox = new Wt::WMessageBox
        ("Help",
         Wt::WString::fromUTF8("<p>Showing Help: {1}</p>").arg(item->text()),
         Wt::Information, Wt::Ok);
        
        messageBox->buttonClicked().connect(std::bind([=] () {
            delete messageBox;
        }));
        
        messageBox->show();
    }, std::placeholders::_1));
    
    Wt::WMenuItem *item = new Wt::WMenuItem("Help");
    item->setMenu(popup);
    rightMenu->addItem(item);
    
    // Add a Search control.
    Wt::WLineEdit *edit = new Wt::WLineEdit();
    edit->setEmptyText("Enter a search item");
    
    edit->enterPressed().connect(std::bind([=] () {
        leftMenu->select(0); // is the index of the "Sales"
        mySpartan->updateProfile(edit->text().toUTF8());
        mySpartan->printRanks();
        std::cout << mySpartan->getGamertag() << std::endl;
        std::cout << mySpartan->getEmblem() << std::endl;
        if (boost::algorithm::contains(mySpartan->getEmblem(), "https:")) {
            // Update summary template
            std::string tmp_url = mySpartan->getEmblem();
            boost::replace_all(tmp_url, "&", "&amp;");
            t->bindString("emblem-url", tmp_url);
            t->bindString("spartan-name", mySpartan->getGamertag());
            t->bindString("spartan-rank", std::to_string(mySpartan->getSpartanRank()));
        
            // Update summary tab
            //tabW->widget(0)->setText(new Wt::WString(mySpartan->getRanks()));
            text->setText(mySpartan->getRanks());
        
            ranks->update();
            recent_matches_panel->update();
        }
    }));
    
    navigation->addSearch(edit, Wt::AlignRight);
    
    container->addWidget(contentsStack);
    
    return container;
}

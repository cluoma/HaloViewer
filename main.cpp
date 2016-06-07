#include <Wt/WApplication>
#include <Wt/WEnvironment>
#include <Wt/WBootstrapTheme>
#include <Wt/WHBoxLayout>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>

//#include <RInside.h>

#include "nav_bar.h"


Wt::WApplication *createApplication(const Wt::WEnvironment& env)
{
    Wt::WApplication* app = new Wt::WApplication(env);
    //HelloApplication *app = new HelloApplication(env);
    // Load bootstrap 3 theme
    Wt::WBootstrapTheme *bootstrapTheme = new Wt::WBootstrapTheme(app);
    bootstrapTheme->setVersion(Wt::WBootstrapTheme::Version3);
    bootstrapTheme->setResponsive(true);
    app->setTheme(bootstrapTheme);
    app->useStyleSheet("resources/themes/bootstrap/3/bootstrap.css");
    //app->useStyleSheet("resources/themes/bootstrap-bare/css/bootstrap.css");
    
    //Wt::WHBoxLayout *layout = new Wt::WHBoxLayout(app->root());
    //layout->setContentsMargins(0, 0, 0, 0);
    //layout->addWidget(nav_bar());
    
    Wt::WContainerWidget *layout = new Wt::WContainerWidget(app->root());
    layout->addStyleClass("container");
    layout->addWidget(nav_bar());
    
    // Set title
    app->setTitle("Halo Viewer");
    
    return app;
}

int main(int argc, char **argv)
{
    //RInside R(argc, argv);              // create an embedded R instance
    
    //R["txt"] = "Colin";	// assign a char* (string) to 'txt'
    
    //Rcpp::CharacterVector v = R.parseEval("paste0('HELLO, ', txt)");          // eval the init string, ignoring any returns
    
    //std::cout << v[0] << std::endl;
    
    return Wt::WRun(argc, argv, &createApplication);
}

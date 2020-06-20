include(GNUInstallDirs)

install(PROGRAMS run-beeview.py webserver.js DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT View)
install(FILES package.json package-lock.json DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT View)
install(DIRECTORY client/html/ DESTINATION "${CMAKE_INSTALL_DATADIR}/www" COMPONENT View)

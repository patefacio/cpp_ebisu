SCRIPT=$(readlink -f "$0")
sudo add-apt-repository --yes ppa:ubuntu-sdk-team/ppa
sudo apt-get update -qq
sudo apt-get install qtbase5-dev qtdeclarative5-dev libqt5webkit5-dev libsqlite3-dev
sudo apt-get install qt5-default qttools5-dev-tools
echo should have qt at!!!
find /usr/include/qt5

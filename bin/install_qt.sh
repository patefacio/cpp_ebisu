SCRIPT=$(readlink -f "$0")
sudo add-apt-repository --yes ppa:ubuntu-sdk-team/ppa
sudo apt-get update -qq
sudo apt-get install qtdeclarative5-dev

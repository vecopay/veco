Linux cross-compile

This guide describes how to build Swamp Core wallet from source under Ubuntu Linux. It is intended to serve as a simple guide for general compilation of non-deterministic binary files from the stable source code. For a more detailed guide, see the macOS Build Notes. A standard installation of Ubuntu Linux 18.04 LTS will be used as an environment for the build. We assume you are running as a user with sudo permissions. First add the necessary extra repository and update all packages:

sudo add-apt-repository ppa:bitcoin/bitcoin
sudo apt update
sudo apt upgrade
Now install the dependencies as described in the installation documentation:

sudo apt install build-essential libtool autotools-dev automake pkg-config libssl-dev libevent-dev bsdmainutils git libdb4.8-dev libdb4.8++-dev curl
sudo apt install libboost-system-dev libboost-filesystem-dev libboost-chrono-dev libboost-program-options-dev libboost-test-dev libboost-thread-dev libzmq3-dev
sudo apt install ca-certificates curl g++ git-core pkg-config autoconf librsvg2-bin libtiff-tools libtool automake faketime bsdmainutils cmake imagemagick libcap-dev libz-dev libbz2-dev python python-dev python-setuptools fonts-tuffy p7zip-full sleuthkit
Optionally install the Qt dependencies if you want to build the Dash GUI:

sudo apt install libqt5gui5 libqt5core5a libqt5dbus5 qttools5-dev qttools5-dev-tools libprotobuf-dev protobuf-compiler
Download the stable Dash repository:

git clone https://github.com/swampcoin/swamp.git
cd swamp
A copy of the macOS SDK is required during the build process. 

download Xcode_7.3.1 frm apple your own way 
OR
To download this, use a Google Chrome in a desktop environment to go to https://appleid.apple.com and create or sign in to your Apple account. Then go to https://developer.apple.com and open the Chrome Developer Tools from the Menu -> More tools -> Developer tools. Click on the Network tab, then go back to your main browser window and copy in the following URL:
https://developer.apple.com/services-account/download?path=/Developer_Tools/Xcode_7.3.1/Xcode_7.3.1.dmg
Cancel the download as soon as it begins and go back to your the Network tab in the developer tools. Right click on the network request at the bottom of the list labeled Xcode_7.3.1.dmg and select Copy -> Copy as cURL (bash). Paste this long string of text into your Linux terminal, append -o Xcode_7.3.1.dmg at the end and then press enter to begin the download. Once it is complete, extract the required files from the disc image as follows:

contrib/macdeploy/extract-osx-sdk.sh
rm -rf 5.hfs MacOSX10.11.sdk
mkdir depends/SDKs
tar sfvx MacOSX10.11.sdk.tar.gz
mv MacOSX10.11.sdk/ depends/SDKs/
And build:

make -C depends HOST=x86_64-apple-darwin11
./autogen.sh
./configure --prefix=`pwd`/depends/x86_64-apple-darwin11
make
~/swamp/src now contains the compiled Swamp binaries, and ~/swamp/src/qt contains the Swamp GUI wallet.

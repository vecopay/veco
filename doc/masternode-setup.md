Send your wallet that will become a masternode 1000 SWAMP.  

Wait for 15 confirmations

open terminal or command line on your linux server

open firewall by entering command: sudo ufw allow 33333

if you have a router you will have to forward port 33333 to your linux server

1. enter command: masternode genkey
    save the response to a text file somewhere
2. enter command: masternode outputs
   remove the quotes and the colon from the result and save the response to a text file somewhere.  It will be something like this before removing the extra stuff
   "Th617hyRHN8kjjkhkjhkjhsdkjfrh676TYGUI": "0"

   and look like this after

   Sh617hyRHN8kjjkhkjhkjhsdkjfrh676TYGUI 0

The end result is a long string and number at the end.  The number will be a 1 or 0. 

Now you are going to update 2 files ending in .conf  These are located in the data directory your wallet is using.  For me it is ~/.swampcore on ubuntu server 18.04.  When installing the wallet you would have chosen the location.  

The first file you will update is named swamp.conf'.  Edit it with any editor you like. I use nano on ubuntu. For me to open the file in nano I enter: sudo nano ~/.swampcore/swamp.conf

Add the following substituting in the info you gathered above<br><br>

listen=1<br>
server=1<br>
daemon=1<br>
rpcuser=any-username-you-want<br>
rpcpassword=any-password-you-want<br>
rpcallowip=127.0.0.1<br>
masternode=1<br>
masternodeprivkey=enter-the-long-string-you-got-from-step-1<br>
externalip=enter-the-public-ip-of-your-linux-server-here:33333<br><br>
    

Save your file.  To save in nano press control and x at the same time, press y to confirm, press enter save

Next we will edit the file named masternode.conf

For me to open the file in nano I enter: sudo nano ~/.swampcore/masternode.conf

Add the following substituting in the info we gathered above. 

mn <your public ip without brackets>:33333 <the result of #2 above without the brackets>

It will end up looking something like this


mn 67.166.248.227:31110 7Wowe2ZWhjRdh1FXxi5UqBqSvGNkx3NsYKY4NLnhStZEJYmMyqg 7422b6e19b55ae41cb153b9be83d50721c666fd78a365763a7d35d2840967d54 1


Save the masternode.conf file.  If using nano press control and x at the same time, press y to confirm, press enter to save

When you restart your wallet you must wait until it's fully in sync and then use command: sudo <path to swamp-cli>/swamp-cli masternode start-alias mn
The "mn" in the command is the name you gave your node.  Feel free to call it anything you like.

You can check status of your masternode by using command: sudo <path to swamp-cli>/swamp-cli masternode status

If you did everything right you will see "Successfully Started" in the message given

Now its time to set up Sentinel to keep things running smoothly and avoid WATCHDOG_EXPIRED status.  Visit https://github.com/swampcoin/sentinel/blob/master/README.md to continue



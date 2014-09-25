# ~/.bashrc: executed by bash(1) for non-login shells.
# see /usr/share/doc/bash/examples/startup-files (in the package bash-doc)
# for examples

# If not running interactively, don't do anything
[ -z "$PS1" ] && return

# don't put duplicate lines in the history. See bash(1) for more options
# ... or force ignoredups and ignorespace
HISTCONTROL=ignoredups:ignorespace

# append to the history file, don't overwrite it
shopt -s histappend

# for setting history length see HISTSIZE and HISTFILESIZE in bash(1)
HISTSIZE=1000
HISTFILESIZE=2000

# check the window size after each command and, if necessary,
# update the values of LINES and COLUMNS.
shopt -s checkwinsize

# make less more friendly for non-text input files, see lesspipe(1)
[ -x /usr/bin/lesspipe ] && eval "$(SHELL=/bin/sh lesspipe)"

# set variable identifying the chroot you work in (used in the prompt below)
if [ -z "$debian_chroot" ] && [ -r /etc/debian_chroot ]; then
    debian_chroot=$(cat /etc/debian_chroot)
fi

# set a fancy prompt (non-color, unless we know we "want" color)
case "$TERM" in
    xterm-color) color_prompt=yes;;
esac

# uncomment for a colored prompt, if the terminal has the capability; turned
# off by default to not distract the user: the focus in a terminal window
# should be on the output of commands, not on the prompt
#force_color_prompt=yes

if [ -n "$force_color_prompt" ]; then
    if [ -x /usr/bin/tput ] && tput setaf 1 >&/dev/null; then
	# We have color support; assume it's compliant with Ecma-48
	# (ISO/IEC-6429). (Lack of such support is extremely rare, and such
	# a case would tend to support setf rather than setaf.)
	color_prompt=yes
    else
	color_prompt=
    fi
fi

if [ "$color_prompt" = yes ]; then
    PS1='${debian_chroot:+($debian_chroot)}\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\]\$ '
else
    PS1='${debian_chroot:+($debian_chroot)}\u@\h:\w\$ '
fi
unset color_prompt force_color_prompt

# If this is an xterm set the title to user@host:dir
case "$TERM" in
xterm*|rxvt*)
    PS1="\[\e]0;${debian_chroot:+($debian_chroot)}\u@\h: \w\a\]$PS1"
    ;;
*)
    ;;
esac

# enable color support of ls and also add handy aliases
if [ -x /usr/bin/dircolors ]; then
    test -r ~/.dircolors && eval "$(dircolors -b ~/.dircolors)" || eval "$(dircolors -b)"
    alias ls='ls --color=auto'
    #alias dir='dir --color=auto'
    #alias vdir='vdir --color=auto'

    alias grep='grep --color=auto'
    alias fgrep='fgrep --color=auto'
    alias egrep='egrep --color=auto'
fi

# some more ls aliases
alias ll='ls -alF'
alias la='ls -A'
alias l='ls -CF'

# Alias definitions.
# You may want to put all your additions into a separate file like
# ~/.bash_aliases, instead of adding them here directly.
# See /usr/share/doc/bash-doc/examples in the bash-doc package.

if [ -f ~/.bash_aliases ]; then
    . ~/.bash_aliases
fi

# enable programmable completion features (you don't need to enable
# this, if it's already enabled in /etc/bash.bashrc and /etc/profile
# sources /etc/bash.bashrc).
if [ -f /etc/bash_completion ] && ! shopt -oq posix; then
    . /etc/bash_completion
fi

## EXPORT
export PATH=.:$PATH:/usr/local/java/jdk1.6.0_16/bin:/usr/local/zend/bin:/home/silver/script
export CLASSPATH=${HOME}/Java/IN404/Java:.
export JAVA_HOME=/usr/local/java/jdk1.6.0_16/bin
export JMFHOME=/usr/lib/jvm/JMF-2.1.1e
export CLASSPATH=${JMFHOME}/lib/jmf.jar:. 
export LD_LIBRARY_PATH=${JMFHOME}/lib:/usr/local/zend/lib
export CLASSPATH=$CLASSPATH:~/Desktop/java_net_RTP/java/net/RTP

##LANCEMENT
cat ~/logo.txt

## OWN ALIASES
alias clear='clear;source ~/.bashrc'

#gimp :
alias gbr='cd /home/silver/Desktop/Creations/Brush;ls'
alias gbrmk='sudo mkdir /usr/share/gimp/2.0/brushes/others'
alias gbrcp='sudo cp * /usr/share/gimp/2.0/brushes/others'
alias gbrrm='sudo rm -R /usr/share/gimp/2.0/brushes/others'

#bashrc
alias bashrc='sudo gedit ~/.bashrc'

#grub :
alias chgrub='sudo gedit /boot/grub/grub.cfg'

#apt-get
alias apti='sudo apt-get install'
alias aptr='sudo apt-get autoremove'

#git
function gitcom () { git commit -a -m "$1" ; }
alias gitadd='git add *'
alias gitup='git pull'
alias gitpush='git push origin master'
function gitacp () { gitadd ; gitcom "$1" ; gitpush ; }

#sql
alias sqlmdp='sudo dpkg-reconfigure mysql-server-5.5'
alias sql='mysql --user=root --password=root'

#cd
alias home='cd ~/'
alias desk='cd ~/Desktop/'
alias fac='cd ~/Desktop/slvr-fac/'
function facl () { cd ~/Desktop/slvr-fac/Fac/Licence/ ; cd IN"$1" ; }
function facm () { cd ~/Desktop/slvr-fac/Fac/Master/ ; cd IN"$1" ; }
alias cmi='cd /var/www/public/cmi2013/Sources/mastering/'
alias social='cd /var/www/public/social-network/'

#raccourcis
alias arduino='~/Softs/arduino-1.0.5/arduino &'
alias netlogo='~/Softs/netlogo-5.0.4/netlogo.sh &'
alias eclipse='~/Softs/eclipse/eclipse &'
alias warbot='~/Desktop/slvr-fac/Fac/Master/IN207/Warbot/launch.sh &'
alias comporg='~/Softs/Component-Organizer/_build/release/bin/comporg_unix &'
alias kicad='kicad &'



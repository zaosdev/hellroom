
#Borramos resources
rm -Rf media
#La volvemos a crear
mkdir media
#Descargamos el zip del dropbox
wget https://www.dropbox.com/sh/mly20ainmf2ak40/AAD0jZAaeTviPFME0Y2b5rExa?dl=1
#Descomprimimos el zip en resources
unzip AAD0jZAaeTviPFME0Y2b5rExa?dl=1 -x / -d media
#Borramos el zip
rm AAD0jZAaeTviPFME0Y2b5rExa?dl=1

#Importante darle permisos a setup.sh con chmod -X setup.sh



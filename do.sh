createDir() {
 if [ ! -e $1 ]
 then
     mkdir -p $1
 fi
}
 
DB_DIR=data
createDir ${DB_DIR}

#       is the lock server running?
objy checkls
if [ $? -eq 0 ];then
        echo "++++ Lock Server is running!"
else
        echo "---- Lock Server is NOT running!"
        objy startlockserver
        if [ $? -eq 0 ];then
                echo "++++ Lock Server started"
        else
                echo "---- Lock Server! did not start"
                exit
        fi
fi

FDNAME=testfd
BOOTFILE=${DB_DIR}/${FDNAME}.boot

if [ -w ${BOOTFILE} ]
then
	objy installfd -bootfile ${BOOTFILE};
	objy cleanupfd -local -bootfile ${BOOTFILE};
    	objy deletefd -bootfile ${BOOTFILE};
fi

objy createFD -fdName ${FDNAME} -fddirp ${DB_DIR}

#objy do -infile ./doschema.txt -bootfile ${BOOTFILE}

#objy do -infile ./docreate.txt -bootfile ${BOOTFILE}

#objy do -infile ./doquery.txt -outfile doqueryresults.txt -bootfile ${BOOTFILE}

#echo "*******************************************************************"
#echo "please see file doqueryresults.txt in this folder for query results output"
#echo "*******************************************************************"


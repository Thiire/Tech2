#!/bin/bash

expend=0
spaces=0
indentation=8
header=0
output="no filename"
first_str=$1

tabs $indentation

usage()
{
    echo "Usage: script_formatter.sh in [-h] [-s] [-i nb_char] [-e] [-o out]

     in                       input file
    -h, --header              header generation
    -s, --spaces              force spaces instead of tabulations for indentation
    -i, --indentation=nb_char number of characters for indentation (8 by default)
    -e, --expand              force do and then keywords on new lines
    -o, --output=out          output file (stdout by default)"
    exit 0
}

if [ -z $first_str ]; then
    exit 84
fi

all_file=''
IFS=''
if [ $first_str != "-help" ]; then
    while read data; do all_file="$all_file$data\n"; done < $1
    all_file="$all_file$data\n"
    if [[ ${all_file:0:11} != "#!/bin/sh\n" ]]; then
        all_file="#!/bin/sh\n\n$all_file"
    fi
else
    usage
fi

print_sh()
{
    echo -e $all_file
}

create_header()
{
    jour=$(date +%Y%m%d)
    year=${jour:0:4}
    month=${jour:4:2}
    day=${jour:6:8}
    if [ ${month} = "01" ]; then
        month="January"
    fi
    if [ ${month} = "02" ]; then
        month="February"
    fi
    if [ ${month} = "03" ]; then
        month="March"
    fi
    if [ ${month} = "04" ]; then
        month="April"
    fi
    if [ ${month} = "05" ]; then
        month="May"
    fi
    if [ ${month} = "06" ]; then
        month="June"
    fi
    if [ ${month} = "07" ]; then
        month="July"
    fi
    if [ ${month} = "08" ]; then
        month="August"
    fi
    if [ ${month} = "09" ]; then
        month="September"
    fi
    if [ ${month} = "10" ]; then
        month="October"
    fi
    if [ ${month} = "11" ]; then
        month="November"
    fi
    if [ ${month} = "12" ]; then
        month="December"
    fi
    if [ "${day:0:1}" = "0" ]; then
        day=${day:1:2}
    fi

    idx=13

    for (( ; idx < ${#all_file} ; idx++ )); do
        if [[ ${all_file:idx:1} = "#" ]]; then
            for (( ; 1 ; idx++)); do
                if [[ ${all_file:idx:2} = "\n" ]]; then
                    stock_header="$stock_header\n"
                    idx=$idx+1
                    break
                fi
                stock_header="$stock_header${all_file:idx:1}"
            done
        elif [[ ${all_file:idx:2} = "\n" ]]; then
            idx=$idx+1
        else
            break
        fi
    done

    stock_header="#\n${stock_header}"

    afterday="th"
    case $day in
        1)
        afterday="st"
        shift;;
        2)
        afterday="nd"
        shift;;
        3)
        afterday="rd"
        shift;;
        *)
        afterday="th"
        shift;;
    esac
    if [ $stock_header = "#\n" ]; then
        all_file="${all_file:0:11}\n#####################\n#\n# $output\n# ${day}${afterday} $month, $year\n#\n#####################\n\n${all_file:idx}"
    else
        all_file="${all_file:0:11}\n#####################\n#\n# $output\n# ${day}${afterday} $month, $year\n$stock_header#####################\n\n${all_file:idx}"
    fi
}

create_indentation()
{
    length=${#all_file}
    stock_tmp=""
    for ((id=0 ; id<$length ; id++))
    do
        if [[ ${all_file:id:2} = "\n" ]]; then
            if [[ ${all_file:id+2:1} = " " ]]; then
                id=$id+1
                id=$id+1
                while [ "${all_file:id:1}" = " " ]; do
                    id=$id+1
                done
                id=$id-1
                stock_tmp="$stock_tmp\n"
            else
                stock_tmp="$stock_tmp\n"
                id=$id+1
            fi
        else
            stock_tmp="$stock_tmp${all_file:id:1}"
        fi
    done
    all_file=$stock_tmp
}

create_bracket()
{
    length=${#all_file}
    for ((id=0 ; id<$length ; id++))
    do
        if [ "${all_file:id:3}" = "\n}" -a "${all_file:id+3:2}" = "\n" ]; then
            if [ -z ${all_file:id+5:1} ]; then
                break
            fi
            if [ "${all_file:id+3:4}" != "\n\n" ]; then
                length=$length+2
                all_file="${all_file:0:id+5}\n${all_file:id+5}"
            fi
        fi
    done
    for ((id=0 ; id<$length; id++))
    do
        if [ "${all_file:id:4}" = "() {" ]; then
            all_file="${all_file:0:id+2}\n${all_file:id+3}"
            length=$length+1
        fi
    done
}

finish_indentation()
{
    length=${#all_file}
    stock_tmp=""
    marge=0
    for ((id=0 ; id<$length ; id++))
    do
        if [[ ${all_file:id:7} = "\nelse " || ${all_file:id:8} = "\nelse\n" ]]; then
            marge=$marge-1
        elif [[ ${all_file:id:7} = "\nelif " || ${all_file:id:8} = "\nelif\n" ]]; then
            marge=$marge-1
        elif [[ ${all_file:id:5} = "\nfi " || ${all_file:id:6} = "\nfi\n" ]]; then
            marge=$marge-1
        elif [[ ${all_file:id:5} = "\ndo " || ${all_file:id:6} = "\ndo\n" ]]; then
            marge=$marge-1
        elif [[ ${all_file:id:7} = "\nthen " || ${all_file:id:8} = "\nthen\n" ]]; then
            marge=$marge-1
        elif [[ ${all_file:id:7} = "\ndone " || ${all_file:id:8} = "\ndone\n" ]]; then
            marge=$marge-1
        elif [[ ${all_file:id:7} = "\nesac " || ${all_file:id:8} = "\nesac\n" ]]; then
            marge=$marge-1
        elif [[ ${all_file:id:5} = "\n}\n" ]]; then
            marge=0
        fi
        if [[ ${all_file:id:2} = "\n" ]];then
            id=$id+2
            stock_tmp="$stock_tmp\n"
            for ((jd=0 ; jd<$marge ; jd++))
            do
                if [[ $spaces = 1 ]]; then
                    for ((yd=0 ; yd<$indentation ; yd++))
                    do
                        stock_tmp="$stock_tmp "
                    done
                else
                    stock_tmp="$stock_tmp\t"
                fi
            done
            if [[ ${all_file:id:5} = "else " || ${all_file:id:6} = "else\n" ]]; then
                marge=$marge+1
            elif [[ ${all_file:id:5} = "elif " || ${all_file:id:6} = "elif\n" ]]; then
                marge=$marge+1
            elif [[ ${all_file:id:3} = "if " || ${all_file:id:4} = "if\n" ]]; then
                marge=$marge+1
            elif [[ ${all_file:id:3} = "do " || ${all_file:id:4} = "do\n" ]]; then
                marge=$marge+1
            elif [[ ${all_file:id:5} = "then " || ${all_file:id:6} = "then\n" ]]; then
                marge=$marge+1
            elif [[ ${all_file:id:6} = "while " || ${all_file:id:6} = "while\n" ]]; then
                marge=$marge+1
            elif [[ ${all_file:id:4} = "for " || ${all_file:id:5} = "for\n" ]]; then
                marge=$marge+1
            elif [[ ${all_file:id:5} = "case " || ${all_file:id:6} = "case\n" ]]; then
                marge=$marge+1
            elif [[ ${all_file:id:3} = "{\n" ]]; then
                marge=$marge+1
            fi
            stock_tmp="$stock_tmp${all_file:id:1}"
        else
            stock_tmp="$stock_tmp${all_file:id:1}"
        fi
    done
    all_file=$stock_tmp
}

create_expend()
{
    length=${#all_file}
    for ((id=0 ; id<$length ; id++))
    do
        if [ "${all_file:id:2}" = "; " -a "${all_file:id+2:2}" = "do" ]; then
            all_file="${all_file:0:id}\n${all_file:id+2}"
        fi
        if [ "${all_file:id:2}" = "; " -a "${all_file:id+2:4}" = "then" ]; then
            all_file="${all_file:0:id}\n${all_file:id+2}"
        fi
        if [ "${all_file:id:2}" = "; " -a "${all_file:id+2:4}" = "done" ]; then
            all_file="${all_file:0:id}\n${all_file:id+2}"
        fi
    done
}

stock_header()
{
    header=1
}

stock_spaces()
{
    spaces=1
}

stock_indentation()
{
    stock=$1
    if [ $stock = "-i" ]; then
        indentation=$2
    else
        indentation=${stock:14}
    fi
    tabs $indentation
}

stock_expend()
{
    expend=1
}

stock_output()
{
    stock=$1
    if [ $stock = "-o" ]; then
        output=$2
    else
        output=${stock:9}
    fi
}

while [ ! $# -eq 0 ]; do
    case "$1" in
        -help)
        exit 84
        ;;
        -h | --header)
        stock_header
        shift
        ;;
        -s | --spaces)
        stock_spaces
        shift
        ;;
        -i | --indentation=*)
        stock_indentation $1 $2
        shift
        ;;
        -e | --expand)
        stock_expend
        shift
        ;;
        -o | --output=*)
        stock_output $1 $2
        shift
        ;;
        *)
        shift
        ;;
    esac
done

if [ $header = 1 ] ; then
    create_header $output
fi
create_indentation $all_file
create_bracket $all_file
if [ $expend = 1 ] ; then
    create_expend $all_file
fi
finish_indentation $all_file
print_sh
exit 0
##!/bin/sh
IMG_FILE_EXT="*.png *.jpeg. *.gif *.tiff *.jpg *.bmp"

case $1 in
    init)
        rm .meem
        shopt -s nullglob
        for image in *.{jpg,jpeg,png,gif,tiff,bmp};do
            image_text=$(convert "$image" -white-threshold 80% -black-threshold 100% -negate png:-|  tesseract stdin stdout|tr -d "\n\f")
            echo "$image/$image_text">>.meem
        done
        shopt -u nullglob
        break
        ;;

    sort)
        fuzzycmp "$2" < .meem |paste -d" " - .meem |cut -f1 -d"/"|sort |sed 's/[^ ]* //'| sxiv -i -a
        break
        ;;

    update)
        cut -f1 -d "/" <.meem |sort | comm -1 -3 - <(ls $IMG_FILE_EXT |sort) | while read -r file_img; do
            if [ -z ${string// }  ]; then
                image_text=$(convert "$file_img" -white-threshold 80% -black-threshold 100% -negate png:-|  tesseract stdin stdout|tr -d "\n\f")
                echo "$file_img/$image_text">>.meem
            fi
        done 
        break
        ;;
esac



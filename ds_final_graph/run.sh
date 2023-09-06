src_file="/home/m11102155/ds_final_graph/main.c"
exe_file="/home/m11102155/ds_final_graph/main"
compile="gcc $src_file -o $exe_file"





$compile
#$exe_file

echo "Compile Finish ............."
echo "Start to Execute ..........."
# echo "ENTER DATASET NAME : "
# read dataset_name
read -p "ENTER DATASET NAME : " dataset_name
echo "==========.......... Dataset = $dataset_name.txt ..........=========="



# dataset_file="/home/m11102155/project/dataset/real_dataset/$dataset_name.txt"
dataset_file="dataset/$dataset_name.txt"
#gt_dataset_file
#exp_file



exe_command="$exe_file $dataset_file"
$exe_command




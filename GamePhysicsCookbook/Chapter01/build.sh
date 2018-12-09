echo "Building..."
# start_time=$(date +%s)
start_time=$SECONDS
g++ -std=c++11 vectors.cpp main.cpp
# end_time=$(date +%s)
end_time=$SECONDS
time_taken=$((end_time-start_time))
# time_taken=$(echo "$END - $START" | bc)
echo "Build Completed. Time taken: $time_taken secs"

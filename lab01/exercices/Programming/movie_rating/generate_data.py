#!/usr/bin/env python3
# this script will generate the content for the log file

import datetime
import random
import os

number_of_log_event = 1000      # 100k line of log
number_of_log_file = 10         # divided into these many file
number_of_user = 943
number_of_movie = 1682
max_rating = 10

file_name_base = 'movie_rating';

file_name_list = [ "{}_{:02d}.txt".format(file_name_base, count)
                  for count in range(1, number_of_log_file + 1) ];

# the format will be
# <userID> <tab> <movieID> <tab> <rating> <tab> <timeStamp>

# <userID> will be digit within the range 1 -> number_of_user
user_id_range = (0, number_of_user - 1)

# <movieID> will be digit within the range 1 -> number_of_movie
movie_id_range = (0, number_of_movie - 1);

# <rating> will be random integer within the range rating_range
rating_range = (0, max_rating)

# <timeStamp> will be random value ranging 30 day back
current_time = datetime.datetime.now()
time_go_back_until = datetime.timedelta(days = -30)
timestamp_range = (current_time + time_go_back_until, current_time)
time_format = "%Y/%m/%dT%H:%M:%S"

def get_random_id(id_range):
    return random.randint(id_range[0], id_range[1])

def get_random_date(time_range):
    delta = time_range[1] - time_range[0]
    int_delta = (delta.days * 24 * 60 * 60) + delta.seconds
    random_second = random.randrange(int_delta)
    return time_range[0] + datetime.timedelta(seconds=random_second)

# start writing to file
directory_path = os.path.join('.', 'data')
os.makedirs(directory_path, exist_ok=True)
log_event_each_file = number_of_log_event // number_of_log_file

for file_name in file_name_list:
    with open(os.path.join(directory_path, file_name), 'w', encoding="utf-8") as current_file:
        for i in range(log_event_each_file):
            content = "{userID}\t{movieID}\t{rating}\t{timeStamp}\n".format(
                    userID = get_random_id(user_id_range),
                    movieID = get_random_id(movie_id_range),
                    rating = get_random_id(rating_range),
                    timeStamp = get_random_date(timestamp_range).strftime(time_format)
                )
            current_file.write(content);

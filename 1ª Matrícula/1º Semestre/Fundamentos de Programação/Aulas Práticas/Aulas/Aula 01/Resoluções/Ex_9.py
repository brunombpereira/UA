starting_time = 6 * 60 + 52

walk_pace = 10
run_pace = 6

training_duration = 1 * walk_pace + 3 * run_pace + 4 * walk_pace

h = (starting_time + training_duration) // 60
m = (starting_time + training_duration) % 60

print(f'Chegou a casa por volta das {h}:{m :.2f}')
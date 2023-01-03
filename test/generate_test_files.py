# A script to generate test files

import random

def generate_file(file_type, num, num_nature):
  # file_type = input("Enter file type(txt/csv): ")
  # num = int(input("How many numbers ? "))
  # num_nature = int(input("Should the numbers be random(1) or sorted(2) or reverse sorted(3) ?"))
  delim = "\n" if file_type == "txt" else ",\n"
  file_name = ''
  if num_nature == 1:
    # will generate random numbers and write to file
    file_name = '{}/random-{}-input.{}'.format(file_type,num,file_type)
    with open(file_name, 'a') as f:
      for i in range(num):
        line = str(random.randint(-num//2, num//2))
        f.write(line+delim)  
  elif num_nature == 2:
    # will generate sorted list of numbers and write to file
    file_name = '{}/sorted-{}-input.{}'.format(file_type,num,file_type)
    with open(file_name, 'a') as f:
      for i in range(-num//2, num//2, 1):
        line = str(i)
        f.write(line+delim)
  elif num_nature == 3:
    # will generate a reverse sorted list of numbers and write to file
    file_name = '{}/rev-sorted-{}-input.{}'.format(file_type,num,file_type)
    with open(file_name, 'a') as f:
      for i in range(num//2, -num//2, -1):
        line = str(i)
        f.write(line+delim)

if __name__=="__main__":
  input_sizes = [10*(2**i) for i in range(0,11)]
  for input_size in input_sizes:
    #generate random txt files
    generate_file('txt',input_size, 1)
    #generate sorted txt files
    generate_file('txt',input_size, 2)
    #generate reverse sorted txt files
    generate_file('txt',input_size, 3)
    #generate random csv files
    generate_file('csv',input_size, 1)
    #generate sorted csv files
    generate_file('csv',input_size, 2)
    #generate reverse sorted csv files
    generate_file('csv',input_size, 3)

import math
import csv

def read_fasta(filename):
    with open(filename) as fasta_file:
        sequence_names = []
        sequences = {}
        for line in fasta_file:
            if line[0] is '>':
                name = line[1:].rstrip('>').rstrip('\n')
                sequence_names.append(name)
                sequences[name] = ''
            else:
                sequences[name] += line.rstrip('\n')
    return sequence_names, sequences


def unmatch_counter(sequence_a, sequence_b):
     # This function requires both sequences to be the same length
    if (len(sequence_a) != len(sequence_b)):
        raise ValueError("Sequences with different length")
    else:
        unmatch_counter = 0
        for i in range(len(sequence_a)):
            if sequence_a[i] is '-' or sequence_b[i] is '-':
                continue
            if sequence_a[i] is not sequence_b[i]:
                unmatch_counter += 1
        return unmatch_counter
 

def p_distance(unmatchs, string_length):
    if unmatchs is 0: 
        return 0
    else:
        return unmatchs/string_length
        
def jukes_cantor(p_distance):
    if p_distance is 0:
        return 0
    else:
        return -(3/4)*math.log(1 - (4/3 * p_distance))

def generating_matrix(sequence_names, sequences):
    p_distances = {}
    jukes_cantor_distances = {}
    for i in range(len(sequence_names)):
        p_distance_list = []
        jukes_cantor_list = []
        for j in range(i):
            p_distance_list.append(0)
            jukes_cantor_list.append(0)
        for j in range(i, len(sequence_names)):
            unmatch = unmatch_counter(sequences[sequence_names[i]], sequences[sequence_names[j]])
            p_dist = p_distance(unmatch, len(sequences[sequence_names[i]]))
            jukes_cantor_dist = jukes_cantor(p_dist)
            p_distance_list.append(p_dist)
            jukes_cantor_list.append(jukes_cantor_dist)
        p_distances[sequence_names[i]] = p_distance_list
        jukes_cantor_distances[sequence_names[i]] = jukes_cantor_list
    return p_distances, jukes_cantor_distances


def write_matrix(sequence_names, matrix, filename):
    with open(filename + '.txt' ,'a') as output:
        for sequence_name in sequence_names:
            output.write(',' + sequence_name)
        output.write('\n')
        for sequence_name in sequence_names:
            output.write(sequence_name)
            for i in range(len(sequence_names)):
                output.write(',' + str(matrix[sequence_name][i]))
            output.write('\n')


filename = input("Type the filename: ")
output_filename = input("Output filename: ")
sequence_names, sequences = read_fasta(filename)
p_matrix, jc_matrix = generating_matrix(sequence_names, sequences)
write_matrix(sequence_names, p_matrix, output_filename + '_p')
write_matrix(sequence_names, jc_matrix, output_filename + '_jc')


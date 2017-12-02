import math
import csv

def read_fasta(filename):
    with open(filename) as fasta_file:
        sequences_name = []
        sequences = []
        for line in fasta_file:
            if line[0] is '>':
                name = line[1:].rstrip('>').rstrip('\n')
                if len(sequences_name) != 0:
                    sequences.append(sequence)
                sequences_name.append(name)
                sequence = ''
            else:
                sequence += line.rstrip('\n')
        sequences.append(sequence)
    return sequences_name, sequences


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

def generating_matrix(sequences_name, sequences):
    p_distances = [] 
    jukes_cantor_distances = []
    for i in range(len(sequences_name)):
        p_distance_list = []
        jukes_cantor_list = []
        for j in range(len(sequences_name)):
            unmatch = unmatch_counter(sequences[i], sequences[j])
            p_dist = p_distance(unmatch, len(sequences[i]))
            jukes_cantor_dist = jukes_cantor(p_dist)
            p_distance_list.append(p_dist)
            jukes_cantor_list.append(jukes_cantor_dist)
        p_distances.append(p_distance_list)
        jukes_cantor_distances.append(jukes_cantor_list)
    return p_distances, jukes_cantor_distances


def write_matrix(sequences_name, matrix, filename):
    with open(filename + '.txt' ,'a') as output:
        for sequence_name in sequences_name:
            output.write(',' + sequence_name)
        output.write('\n')
        for i in range(len(matrix)):
            output.write(sequences_name[i])
            for j in range(len(matrix)):
                output.write(',' + str(matrix[i][j]))
            output.write('\n')


def UPGMA(sequences_name, matrix):
    if len(sequences_name) == 2:
        return str( '(' + sequences_name[0] + ',' + sequences_name[1] + ');')
    else:
        to_be_joined = ()
        value = matrix[0][1]
        new_matrix = []
        matrix_keys = []
        for i in range(len(matrix)):
            for j in range(i + 1, len(matrix)):
                if matrix[i][j] < value:
                    value = matrix[i][j]
                    to_be_joined = (i, j)
        for i in range(len(matrix)):
            if i == to_be_joined[0] or i == to_be_joined[1]:
                continue
            else:
                distances = []
                for j in range(len(matrix)):
                    if j == to_be_joined[0] or j == to_be_joined[0]:
                        continue
                    else: 
                        distances.append(matrix[i][j])
                distances.append((matrix[i][to_be_joined[0]] + matrix[i][to_be_joined[1]]) / 2)
                new_matrix.append(distances)
                matrix_keys.append(sequences_name[i])
        joined = []
        for i in range(len(new_matrix)):
            joined.append(new_matrix[i][len(new_matrix)])
        joined.append(0)
        new_matrix.append(joined)
        matrix_keys.append('(' + sequences_name[to_be_joined[0]] + ',' + sequences_name[to_be_joined[1]] + ')')
        print('{:8}'.format(''), end='')
        for key in matrix_keys:
            print(key[:7]+' ', end='')
        print ('\n', end='')
        for i in range(len(new_matrix)):
            print(matrix_keys[i][:7], end=' ')
            for j in range(len(new_matrix)):
                print('{:.5f}'.format(new_matrix[i][j]), end=' ')
            print('\n', end='')
        print(matrix_keys[-1])
        return UPGMA(matrix_keys, new_matrix)

    


filename = input("Type the filename: ")
output_filename = input("Output filename: ")
sequences_name, sequences = read_fasta(filename)
p_matrix, jc_matrix = generating_matrix(sequences_name, sequences)
upgma_jc = UPGMA(sequences_name, jc_matrix)
upgma_p = UPGMA(sequences_name, p_matrix)
write_matrix(sequences_name, p_matrix, output_filename + '_p')
write_matrix(sequences_name, jc_matrix, output_filename + '_jc')
with open(output_filename + '_jc.nwk', 'w') as output:
    output.write(upgma_jc)
with open(output_filename + '_p.nwk', 'w') as output:
    output.write(upgma_p)

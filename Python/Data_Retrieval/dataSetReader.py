import numpy

class Datasets:
    """
    This class stores ALL of the data. The training, testing, and validation
    data is all stored here as instances of the Dataset class.
    """
    def __init__(self, train, test):
        self.train = train
        self.test = test

def createDataset(filePath):
    """
    Given a file path, this method will read through the file and create
    a the inputs and outputs for a single Dataset then it will return a
    Dataset instance.
    """
    #create np array with all the numbers
    #reshape the array to (numMultisets, numElementsPerSet)
    with open(filePath) as file:
        line = file.readline()
        num_examples, elements_per_multiset, elements_per_label = eval(line)
        
        dt = numpy.dtype(numpy.float32)
        dataset = []

        for i in range(num_examples):
            multisets = numpy.array([], dt)
            labels = numpy.array([], dt)
            allNums = eval(file.readline())
            for num in allNums:
                multisets = numpy.append(multisets, num)
            allLabels = eval(file.readline())
            for num in allLabels:
                labels = numpy.append(labels, num)
            multisets = multisets.reshape(elements_per_multiset, 1)
            labels = labels.reshape(2, 1)
            my_tuple = multisets, labels
            dataset.append(my_tuple)

    return dataset, elements_per_multiset, elements_per_label

def read_data_sets():
    """
    This method creates the training, testing and validation instances of
    the Dataset class then it returns them all grouped up in an instance
    of the Datasets class.
    """
    train, num_of_inputs1, num_of_labels1 = createDataset("training-multisets.txt")
    test, num_of_inputs2, num_of_labels2 =  createDataset("testing-multisets.txt")
    assert num_of_inputs1 == num_of_inputs2, 'The number of inputs needs to be the same in both training and testing datasets!'
    assert num_of_labels1 == num_of_labels2, 'The number of labels needs to be the same in both training and testing datasets!'
    return Datasets(train=train, test=test), num_of_inputs1, num_of_labels1

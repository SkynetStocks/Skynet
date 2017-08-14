import numpy

class Dataset:
    def __init__(self, multisets, labels):
        self._num_examples = multisets.shape[0]
        self._multisets = multisets
        self._labels = labels
        self._epochs_completed = 0
        self._index_in_epoch = 0

    @property
    def multisets(self):
        return self._multisets

    @property
    def labels(self):
        return self._labels

    @property
    def num_examples(self):
        return self._num_examples

    @property
    def epochs_competed(self):
        return self._epochs_completed
        
    def next_batch(self, batch_size, shuffle=True):
        """Return the next `batch_size` examples from this data set."""
        start = self._index_in_epoch
        # Shuffle for the first epoch
        if self._epochs_completed == 0 and start == 0 and shuffle:
            perm0 = numpy.arange(self._num_examples)
            numpy.random.shuffle(perm0)
            self._multisets = self.multisets[perm0]
            self._labels = self.labels[perm0]
        # Go to the next epoch
        if start + batch_size > self._num_examples:
            # Finished epoch
            self._epochs_completed += 1
            # Get the rest examples in this epoch
            rest_num_examples = self._num_examples - start
            multisets_rest_part = self._multisets[start:self._num_examples]
            labels_rest_part = self._labels[start:self._num_examples]
            # Shuffle the data
            if shuffle:
                perm = numpy.arange(self._num_examples)
                numpy.random.shuffle(perm)
                self._multisets = self.multisets[perm]
                self._labels = self.labels[perm]
            # Start next epoch
            start = 0
            self._index_in_epoch = batch_size - rest_num_examples
            end = self._index_in_epoch
            multisets_new_part = self._multisets[start:end]
            labels_new_part = self._labels[start:end]
            return numpy.concatenate((multisets_rest_part, multisets_new_part), axis=0) , numpy.concatenate((labels_rest_part, labels_new_part), axis=0)
        else:
            self._index_in_epoch += batch_size
            end = self._index_in_epoch
            return self._multisets[start:end], self._labels[start:end] 

class Datasets:
    def __init__(self, train, test):
        self.train = train
        self.test = test

def readNextInt(myStr):
    endIndex = myStr.find(',')
    num = myStr[:endIndex]
    num = int(num)
    return num, endIndex

def readNextFloat(myStr):
    endIndex = myStr.find(',')
    if endIndex != -1:
        num = myStr[:endIndex]
    else:
        num = myStr
    num = float(num)
    return num, endIndex

def createDataset(filePath):
    #create np array with all the numbers
    #reshape the array to (numMultisets, numElementsPerSet)
    with open(filePath) as file:
        line = file.readline()
        num_examples, endIndex = readNextInt(line)
        line = line[endIndex + 1:]
        elementsPerMultiset, endIndex = readNextInt(line)
        
        dt = numpy.dtype(numpy.float32)
        multisets = numpy.array([], dt)
        labels = numpy.array([], dt)

        for i in range(num_examples):
            line = file.readline()
            for j in range(elementsPerMultiset):
                num, endIndex = readNextFloat(line)
                multisets = numpy.append(multisets, num)
                line = line[endIndex + 1:]
            num, endIndex = readNextFloat(line)
            labels = numpy.append(labels, num)

    multisets = multisets.reshape(num_examples, elementsPerMultiset)
        
    return Dataset(multisets, labels);

def read_data_sets():
    train = createDataset("training-multisets.txt")
    test =  createDataset("testing-multisets.txt")
    return Datasets(train=train, test=test)

read_data_sets()

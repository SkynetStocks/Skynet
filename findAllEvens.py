import numpy
import tensorflow as tf

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

# Import data
allData = read_data_sets()
  
# Create the model
x = tf.placeholder(tf.float32, [None, 5])
W = tf.Variable(tf.zeros([5, 1]))
b = tf.Variable(tf.zeros([1]))
y = tf.matmul(x, W) + b

# Define loss and optimizer
y_ = tf.placeholder(tf.float32, [None, 1])

# The raw formulation of cross-entropy,
#
#   tf.reduce_mean(-tf.reduce_sum(y_ * tf.log(tf.nn.softmax(y)),
#                                 reduction_indices=[1]))
#
# can be numerically unstable.
#
# So here we use tf.nn.softmax_cross_entropy_with_logits on the raw
# outputs of 'y', and then average across the batch.
cross_entropy = tf.reduce_mean(
  tf.nn.softmax_cross_entropy_with_logits(labels=y_, logits=y))
train_step = tf.train.GradientDescentOptimizer(0.5).minimize(cross_entropy)

sess = tf.InteractiveSession()
tf.global_variables_initializer().run()
# Train
for _ in range(1000):
    batch_xs, batch_ys = allData.train.next_batch(5)
    sess.run(train_step, feed_dict={x: batch_xs, y_: batch_ys})

# Test trained model
correct_prediction = tf.equal(tf.argmax(y, 1), tf.argmax(y_, 1))
accuracy = tf.reduce_mean(tf.cast(correct_prediction, tf.float32))
print(sess.run(accuracy, feed_dict={x: allData.test.images,
                                  y_: allData.test.labels}))


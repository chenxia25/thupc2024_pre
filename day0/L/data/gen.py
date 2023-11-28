import random
import os
import copy
import datetime
import numpy as np

TASK_NUM = 1

N_LIMIT = 1000
R_LIMIT = 1000
K_LIMIT = 1000000
Q_LIMIT = 1000

def log(string):
	print(string, flush = True)
	with open("gen.log", "a") as f:
		f.write("[{}] {}\n".format(datetime.datetime.now(), string))

def rotate_y(angle):
	return np.mat([
		[np.cos(angle), 0, np.sin(angle)],
		[0, 1, 0],
		[-np.sin(angle), 0, np.cos(angle)]
	])

def rotate_z(angle):
	return np.mat([
		[np.cos(angle), -np.sin(angle), 0],
		[np.sin(angle), np.cos(angle), 0],
		[0, 0, 1]
	])

def rotate_to_north(theta, phi):
	return rotate_z(phi) * rotate_y(-theta) * rotate_z(-phi)

def between(o, a, b, c):
	rotate = rotate_to_north(o)
	a = rotate * np.mat(a).reshape(3, 1)
	b = rotate * np.mat(b).reshape(3, 1)
	c = rotate * np.mat(c).reshape(3, 1)
	a = np.arctan2(a[1, 0], a[0, 0])
	b = np.arctan2(b[1, 0], b[0, 0])
	c = np.arctan2(c[1, 0], c[0, 0])
	if c < a:
		c += np.pi * 2
	if c - a > np.pi:
		a, c = c, a + np.pi * 2
		if a > np.pi:
			a -= np.pi * 2
			c -= np.pi * 2
	return a <= b <= c

def intersect(p1, p2, q1, q2):
	a1 = copy.deepcopy(p1)
	a2 = copy.deepcopy(p2)
	b1 = copy.deepcopy(q1)
	b2 = copy.deepcopy(q2)

	return between(p1, q1, p2, q2) and between(p2, q1, p1, q2) and between(q1, p1, q2, p2) and between(q2, p1, q1, p2)

def genChain(n, m):
	r = np.random.uniform(100, R_LIMIT)
	towers = []
	ratio = np.random.uniform(-1, 1)
	for i in range(n):
		towers.append((i / n, ratio * 2 * i / n, np.random.uniform(1, Q_LIMIT)))
	return n, n - 1, 1, n, r, np.random.uniform(1, K_LIMIT), towers, [(i, i + 1) for i in range(1, n)]

def genGrid(n, m, use_polars = True):
	assert n == 31 * 32 + 2
	r = np.random.uniform(100, R_LIMIT)
	towers = [(1, 0, np.random.uniform(1, Q_LIMIT))]
	edges = []
	als = np.linspace(1, 0, 32, endpoint = False)
	bls = np.linspace(0, 2, 32, endpoint = False)
	for j in range(32):
		edges.append((1, 2 + j))
	for i in range(1, 32):
		for j in range(32):
			towers.append((als[i], bls[j], np.random.uniform(1, Q_LIMIT)))
			edges.append((2 + (i - 1) * 32 + j, 2 + (i - 1) * 32 + (j + 1) % 32))
	for i in range(1, 31):
		for j in range(32):
			edges.append((2 + (i - 1) * 32 + j, 2 + i * 32 + j))
			continue
			if np.random.choice([0, 1]):
				edges.append((2 + (i - 1) * 32 + j, 2 + i * 32 + (j + 1) % 32))
			else:
				edges.append((2 + (i - 1) * 32 + (j + 1) % 32, 2 + i * 32 + j))
	towers.append((0, 0, np.random.uniform(1, Q_LIMIT)))
	assert len(towers) == n
	for j in range(32):
		edges.append((n, n - j - 1))
	if use_polars:
		return n, len(edges), 1, n, r, np.random.uniform(1, K_LIMIT), towers, edges
	else:
		s, t = random.sample(list(range(1, n + 1)), 2)
		return n, len(edges), s, t, r, np.random.uniform(1, K_LIMIT), towers, edges

def genTestcase(filename, gen, n, m, shuffle_nodes = False, **extra_param):
	log("Generating input for case {}, params: {} {} {} {}".format(filename, gen.__name__, n, m, extra_param))
	# assert ..., "Parameters invalid!"
	if not extra_param:
		n, m, s, t, r, k, towers, edges = gen(n, m)
	else:
		n, m, s, t, r, k, towers, edges = gen(n, m, **extra_param)
	node_id = list(range(1, n + 1))
	if shuffle_nodes:
		random.shuffle(node_id)
	node_id = [0] + node_id
	# random.shuffle(edges)
	with open("{}.in".format(filename), "w") as f:
		# f.write("{} {} {}\n{}\n".format(n, l, r, " ".join(list(map(str, s)))))
		f.write("{} {} {} {}\n".format(n, m, s, t))
		f.write("{:.4f} {:.4f}\n".format(r, k))
		for i in range(1, n + 1):
			f.write("{:.4f} {:.4f} {:.4f}\n".format(*towers[node_id[i] - 1]))
		for edge in edges:
			f.write("{} {}\n".format(node_id[edge[0]], node_id[edge[1]]))
	log("Generating output for case {}".format(filename))
	os.system('(time ../ShinyRacers/std < {}.in > {}.ans) 2>> gen.log'.format(filename, filename))

class Cases:
	def __init__(self, prefix = ""):
		self.cnt = 0
		self.prefix = prefix
	
	def gen(self, gen, n, m, **extra_param):
		self.cnt += 1
		genTestcase("{}{}".format(self.prefix, self.cnt), gen, n, m, **extra_param)
	
	def skip(self, cnt = 1):
		self.cnt += cnt

os.system("rm gen.log")
testcase = Cases()
# precase = Cases("../pre/")
# sample = Cases("../down/")

for i in range(1, TASK_NUM + 1):
	log("Generating subtask {}".format(i))
	pre = testcase.cnt
	# pre_pre = precase.cnt
	# add testcases below
	
	testcase.gen(genChain, 1000, 999)
	for cnt in range(9):
		testcase.gen(genGrid, 31 * 32 + 2, 0, use_polars = [True, False][random.randint(0, 1)])
	
	# add testcases above		
	log("Subtask {} done. ({} - {})".format(i, pre + 1, testcase.cnt))
	# log("Subtask {} done. (test: {} - {}; pre: {} - {})".format(i, pre + 1, testcase.cnt, pre_pre + 1, precase.cnt))

# for duck
# os.system("mkdir download")
# os.system("cp ../down/* ./download/")

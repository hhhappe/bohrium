import util


class test_accumulate_views:
    """ Test accumulate of all kind of views"""
    def init(self):
        for cmd, shape in util.gen_random_arrays("R", 4, dtype="np.float32"):
            cmd = "R = bh.random.RandomState(42); a = %s; " % cmd
            for i in range(len(shape)):
                yield (cmd, i)
            for i in range(len(shape)):
                yield (cmd, -i)

    def test_accumulate(self, arg):
        (cmd, axis) = arg
        cmd += "res = M.add.accumulate(a, axis=%d)" % axis
        return cmd

class test_accumulate_primitives:
    def init(self):
        for op in ["add", "multiply"]:
            yield (op, "np.float64")

    def test_vector(self, arg):
        (op, dtype) = arg
        cmd = "R = bh.random.RandomState(42); a = R.random(10, dtype=%s, bohrium=BH); " % dtype
        cmd += "res = M.%s.accumulate(a)" % op
        return cmd


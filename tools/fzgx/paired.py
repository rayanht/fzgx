"""Native MWCC paired-float expressions, without inline assembly."""
VECTOR = '__vec2x32float__'


class Paired:
    def __init__(self, name):
        self.prefix = name + '_paired'
        self.helpers = set()

    def lane(self, expression, index=0):
        self.helpers.add('lane' + str(index))
        return f'{self.prefix}_lane{index}({expression})'

    def pair(self, left, right):
        self.helpers.add('pair')
        return f'{self.prefix}_pair({left}, {right})'

    def expression(self, op, args, vector, scalar):
        if op in ('ps_add', 'ps_sub', 'ps_mul', 'ps_div'):
            operator = dict(ps_add='+', ps_sub='-', ps_mul='*', ps_div='/')[op]
            return f'({vector(args[1])} {operator} {vector(args[2])})'
        if op in ('ps_madd', 'ps_msub'):
            operator = '+' if op == 'ps_madd' else '-'
            return f'({vector(args[1])} * {vector(args[2])} {operator} {vector(args[3])})'
        if op in ('ps_muls0', 'ps_muls1', 'ps_madds0', 'ps_madds1'):
            lane = int(op[-1])
            factor = scalar(args[2]) if lane == 0 else self.lane(vector(args[2]), 1)
            value = f'({vector(args[1])} * {factor})'
            if op.startswith('ps_madds'):
                value = f'({value} + {vector(args[3])})'
            return value
        if op.startswith('ps_merge') and op[-2:] in ('00', '01', '10', '11'):
            return self.pair(self.lane(vector(args[1]), int(op[-2])), self.lane(vector(args[2]), int(op[-1])))
        if op == 'ps_mr':
            return vector(args[1])
        return None

    def declarations(self):
        lines = []
        for helper in sorted(self.helpers):
            union = f'union {{ {VECTOR} ps; float lane[2]; }} value;'
            if helper == 'pair':
                lines.append(f'static inline {VECTOR} {self.prefix}_pair(float a, float b) {{\n'
                             f'    {union}\n    value.lane[0] = a;\n    value.lane[1] = b;\n    return value.ps;\n}}')
            else:
                lines.append(f'static inline float {self.prefix}_{helper}({VECTOR} a) {{\n'
                             f'    {union}\n    value.ps = a;\n    return value.lane[{helper[-1]}];\n}}')
        return lines

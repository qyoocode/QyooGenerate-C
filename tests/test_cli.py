"""Small deterministic CLI regressions; outputs stay in ignored .codex-work."""
import pathlib
import subprocess
import unittest
import xml.etree.ElementTree as ET

ROOT = pathlib.Path(__file__).resolve().parents[1]
OUT = ROOT / '.codex-work' / 'tests'
OUT.mkdir(parents=True, exist_ok=True)
BIN = ROOT / 'bin' / 'qyoo'


class CLI(unittest.TestCase):
    def run_qyoo(self, *args):
        return subprocess.run([str(BIN), *args], cwd=ROOT / 'src', capture_output=True)

    def test_invalid_inputs(self):
        cases = [[], ['-id'], ['-id', '0', '-o'], ['-id', '0', '-w'],
                 ['-id', '0', '-h'], ['-id', '0', '-fg'], ['-id', '0', '-dot'],
                 ['-id', '0', '-bg'], ['-id', '-1'], ['-id', '+1'],
                 ['-id', ''], ['-id', '12x'], ['-id', ' 1'],
                 ['-id', '68719476736'], ['-id', '18446744073709551616'],
                 ['-id', '1' * 37], ['-id', '0', '-w', '0'],
                 ['-id', '0', '-h', '-1'], ['-id', '0', '-w', '4097'],
                 ['-id', '0', '-h', '12x'], ['-id', '0', '-fg', "#fff'bad"],
                 ['-id', '0', '-dot', 'xyz123']]
        for args in cases:
            with self.subTest(args=args):
                result = self.run_qyoo(*args)
                self.assertGreater(result.returncode, 0, result.stderr)

    def test_boundaries_and_row_major_bits(self):
        for number in [0, 1, 2, 32, 1 << 35, 34359738368, 68719476735, 22906492245]:
            bits = format(number, '036b')
            contents = []
            for value in [str(number), bits]:
                target = OUT / ('vector-' + value + '.svg')
                result = self.run_qyoo('-id', value, '-o', str(target))
                self.assertEqual(result.returncode, 0, result.stderr)
                tree = ET.parse(target).getroot()
                dots = tree.findall('{http://www.w3.org/2000/svg}circle')[1:]
                expected = [(179 + col * 180 // 6, 179 + row * 180 // 6)
                            for row in range(6) for col in range(6)
                            if bits[row * 6 + col] == '1']
                self.assertEqual([(int(dot.attrib['cx']), int(dot.attrib['cy'])) for dot in dots], expected)
                contents.append(target.read_bytes())
            self.assertEqual(*contents)

    def test_png_header(self):
        target = OUT / 'boundary.png'
        result = self.run_qyoo('-id', '68719476735', '-w', '64', '-h', '64', '-o', str(target))
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertEqual(target.read_bytes()[:8], b'\x89PNG\r\n\x1a\n')

    def test_unwritable_outputs_fail(self):
        for suffix in ['png', 'svg']:
            result = self.run_qyoo('-id', '1', '-o', str(OUT / 'missing-directory' / ('out.' + suffix)))
            self.assertGreater(result.returncode, 0, result.stderr)

    def test_transparent_svg_fill(self):
        target = OUT / 'transparent.svg'
        result = self.run_qyoo('-id', '1', '-fg', 'transparent', '-o', str(target))
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertNotIn(b'#transp', target.read_bytes())


if __name__ == '__main__':
    unittest.main()

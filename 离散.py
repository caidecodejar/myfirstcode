def is_variable(c):
    """检查字符是否为命题变元（单个字母）"""
    return c.isalpha()

def is_legal_formula(formula, index=0):
    """递归检查公式合法性并收集变元"""
    if index >= len(formula):
        return False, index, set()
    
    c = formula[index]
    variables = set()
    
    # 处理否定符号
    if c == '¬':
        valid, new_index, vars_ = is_legal_formula(formula, index + 1)
        return valid, new_index, vars_
    
    # 处理命题变元
    if is_variable(c):
        return True, index + 1, {c}
    
    # 处理括号表达式
    if c == '(':
        # 检查左子公式
        left_valid, left_index, left_vars = is_legal_formula(formula, index + 1)
        if not left_valid:
            return False, index, set()
        
        if left_index >= len(formula):
            return False, index, set()
        
        # 检查联结词
        connective = formula[left_index]
        if connective not in {'∧', '∨', '→', '↔'}:
            return False, index, set()
        
        # 检查右子公式
        right_valid, right_index, right_vars = is_legal_formula(formula, left_index + 1)
        if not right_valid:
            return False, index, set()
        
        # 检查右括号
        if right_index >= len(formula) or formula[right_index] != ')':
            return False, index, set()
        
        variables = left_vars.union(right_vars)
        return True, right_index + 1, variables
    
    return False, index, set()

def evaluate_formula(formula, var_values):
    """递归计算命题公式的值"""
    stack = []
    current_op = None
    
    for c in formula:
        if is_variable(c):
            stack.append(var_values[c])
        elif c == '¬':
            stack.append(not stack.pop())
        elif c in {'∧', '∨', '→', '↔'}:
            current_op = c
        elif c == '(':
            stack.append(c)
        elif c == ')':
            # 处理括号内的表达式
            right = stack.pop()
            op = stack.pop()
            left = stack.pop()
            
            if op == '∧':
                res = left and right
            elif op == '∨':
                res = left or right
            elif op == '→':
                res = (not left) or right
            elif op == '↔':
                res = left == right
            
            stack.append(res)
    
    return stack[0]

def generate_truth_table(formula):
    """生成命题公式的真值表"""
    valid, _, variables = is_legal_formula(formula)
    if not valid:
        return None, "非法公式"
    
    variables = sorted(variables)
    n = len(variables)
    rows = []
    
    # 生成所有可能的真值组合
    for i in range(2**n):
        values = {}
        for j, var in enumerate(variables):
            values[var] = bool((i >> (n - 1 - j)) & 1)
        
        result = evaluate_formula(formula, values)
        rows.append({**values, 'result': result})
    
    return variables, rows

def generate_principal_forms(variables, truth_table):
    """生成主析取范式和主合取范式"""
    if not truth_table:
        return "无法生成范式：非法公式"
    
    # 主析取范式（所有成真赋值的合取式的析取）
    disjunctive_terms = []
    # 主合取范式（所有成假赋值的析取式的合取）
    conjunctive_terms = []
    
    for row in truth_table:
        if row['result']:  # 成真赋值
            term = []
            for var in variables:
                if row[var]:
                    term.append(var)
                else:
                    term.append(f"¬{var}")
            disjunctive_terms.append(f"({'∧'.join(term)})")
        else:  # 成假赋值
            term = []
            for var in variables:
                if not row[var]:
                    term.append(var)
                else:
                    term.append(f"¬{var}")
            conjunctive_terms.append(f"({'∨'.join(term)})")
    
    # 构建范式字符串
    principal_disjunctive = "∨".join(disjunctive_terms) or "∅（永假式）"
    principal_conjunctive = "∧".join(conjunctive_terms) or "∅（永真式）"
    
    return f"主析取范式：{principal_disjunctive}\n主合取范式：{principal_conjunctive}"

def main():
    """主函数：处理用户输入并展示结果"""
    formula = input("请输入命题公式（支持 ¬, ∧, ∨, →, ↔, 括号和变元，如 (p∧¬q)→r）：").strip()
    
    variables, table = generate_truth_table(formula)
    if table is None:
        print(table)
        return
    
    # 打印真值表
    print("\n真值表：")
    header = " | ".join(variables) + " | 结果"
    separator = "-" * len(header)
    print(separator)
    print(header)
    print(separator)
    
    for row in table:
        values = [str(int(row[var])) for var in variables]
        values.append("T" if row['result'] else "F")
        print(" | ".join(values))
    print(separator)
    
    # 打印主范式
    print("\n范式：")
    print(generate_principal_forms(variables, table))

if __name__ == "__main__":
    main()

import os
import re

def rename_files(folder_path):
    """
    将文件夹内符合特定格式的文件重命名为 A_数字.BMP
    原格式：A__Record_..._数字.BMP
    新格式：A_数字.BMP
    """
    # 确保文件夹路径存在
    if not os.path.exists(folder_path):
        print(f"错误：文件夹 '{folder_path}' 不存在")
        return
    
    # 获取文件夹内所有 .BMP 文件
    files = [f for f in os.listdir(folder_path) if f.endswith('.BMP')]
    
    # 正则表达式匹配：A__Record_..._数字.BMP
    # 匹配最后的下划线后面的数字部分
    pattern = re.compile(r'^A__Record_.*?_(\d+)\.BMP$')
    
    renamed_count = 0
    skipped_count = 0
    
    for filename in files:
        match = pattern.match(filename)
        if match:
            number = match.group(1)
            new_name = f"A_{number}.BMP"
            
            old_path = os.path.join(folder_path, filename)
            new_path = os.path.join(folder_path, new_name)
            
            # 如果新文件名已存在，跳过并提示
            if os.path.exists(new_path):
                print(f"跳过：{new_name} 已存在（原文件：{filename}）")
                skipped_count += 1
                continue
            
            os.rename(old_path, new_path)
            print(f"重命名：{filename} -> {new_name}")
            renamed_count += 1
        else:
            # 不符合格式的文件
            print(f"忽略：{filename}（格式不匹配）")
            skipped_count += 1
    
    print(f"\n{'='*50}")
    print(f"完成！共重命名 {renamed_count} 个文件，跳过 {skipped_count} 个文件。")
if __name__ == "__main__":

    target_folder = os.path.dirname(os.path.abspath(__file__))
    
    rename_files(target_folder)

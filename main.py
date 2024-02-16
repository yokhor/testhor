import os
import time
from datetime import datetime
from math import log

from aiogram import Bot, Dispatcher, executor, types

API_TOKEN = open('.bot_token.txt').read()[:-1]
bot = Bot(token=API_TOKEN)
dp = Dispatcher(bot)
testing_now = False
ready_to_test = False
test_all = False
max_test = 1000
version = '1.0.0'
test_task = ''
wait_for_task = False
OK_id = 'CAACAgIAAxkBAAEpghNlztFU77255cb7S7P0kuxJuUlk3AACyhwAAr3CaUrh1-tMfj4SxDQE'
WA_id = 'CAACAgIAAxkBAAEpghdlztKYz3rNBKhh65eVwe3e3G--VQACdhwAAmchOUrsK9bEwSeQKjQE'


@dp.message_handler(commands=['klenin'])
async def dev(message: types.Message):
    await message.answer('Семь бед — один ответ: Костыль и велосипед!')


@dp.message_handler(commands=['start'])
async def send_welcome(message: types.Message):
    await message.answer(open('greet.txt').read() + '\nversion ' + version)


@dp.message_handler(commands=['test'])
async def test_request(message: types.Message):
    global ready_to_test, testing_now, test_task, wait_for_task
    if testing_now:
        await message.answer('Another solution is currently being tested!')
        return
    await message.answer('OK, now choose the task you\'d like to test (print its number):')
    await message.answer(open('tasks.txt').read(), parse_mode='MarkdownV2', disable_web_page_preview=True)
    wait_for_task = True


# @dp.message_handler(commands=['test_all'])
# async def send_welcome(message: types.Message):  # rewrite
#     global test_all
#     test_all = True
#     await message.answer('All the documents sent will be handled as solutions\n'
#                          'To disable type /test_all again.')


@dp.message_handler(commands=['stop'])
async def stop_testing(message: types.Message):
    global testing_now, ready_to_test
    testing_now = False
    ready_to_test = False
    os.chdir('../..')


async def check(message, verdict_message, run_package):
    global testing_now, ready_to_test, test_task
    ready_to_test = False
    testing_now = True
    start_time = time.time()
    last_log_test = 1
    os.chdir(f'tasks/{test_task}')

    for i in range(1, max_test):
        if not testing_now:
            await message.answer('Testing has been suspended by the user.')
            return
        os.system(f'./gen > input.txt ' + str(i))
        os.system(f'./jury < input.txt > answer.txt')
        if os.system(f'{run_package} < input.txt > user.txt') != 0:
            await message.answer('Runtime error O_o')
        good_answer = open('answer.txt').read()
        bad_answer = open('user.txt').read()
        good_answer = good_answer[:-1] if good_answer[-1] == '\n' else good_answer
        bad_answer = bad_answer[:-1] if bad_answer[-1] == '\n' else bad_answer
        if good_answer != bad_answer:
            await message.answer(f'failed at test {i}')
            await message.answer_document(types.InputFile('input.txt'))
            await message.answer_document(types.InputFile('answer.txt'))
            if bad_answer != "":
                await message.answer_document(types.InputFile('user.txt'))
                await bot.send_sticker(chat_id=message.chat.id, sticker=WA_id)
            else:
                await message.answer('Your answer is empty :/')
            testing_now = False
            os.chdir('../..')
            return
        elif time.time() - start_time >= log(last_log_test):
            start_time = time.time()
            last_log_test = i
            now = datetime.now()
            current_time = now.strftime("%H:%M:%S")
            await verdict_message.edit_text(f'OK {i} | {current_time}')
    await message.answer(str(max_test) +
                         ' tests have been passed, looks like your solution is correct or our generator is weak.')
    await bot.send_sticker(chat_id=message.chat.id, sticker=OK_id)
    testing_now = False
    os.chdir('../..')


async def handle_cpp(message, file_path):
    global test_task
    await bot.download_file(file_path=file_path, destination=f'tasks/{test_task}/package.cpp', timeout=60)
    await message.answer('downloaded successfully')

    if os.system(f'g++ tasks/{test_task}/package.cpp -o tasks/{test_task}/package') == 0:
        await message.answer('compiled successfully')
    else:
        await message.answer('compilation error :(')
        return
    return './package'


async def handle_py(message, file_path):
    global test_task
    await bot.download_file(file_path=file_path, destination=f'tasks/{test_task}/package.py', timeout=60)
    await message.answer('downloaded successfully')
    return 'python3 package.py'


@dp.message_handler(content_types=['document'])  # actions when receiving a document
async def handle_package(message: types.Message):  # probably to assert only .cpp or .txt?
    global ready_to_test, test_all, test_task
    if not test_all and not ready_to_test:
        return
    if testing_now:
        await message.answer('Another solution is currently being tested!')
        return
    file_id = message.document.file_id
    file = await bot.get_file(file_id)
    file_path = file.file_path

    split_tup = os.path.splitext(file_path)
    file_extension = split_tup[1]
    run_package = ''
    if file_extension in ['.cpp', '.txt']:
        run_package = await handle_cpp(message, file_path)
    elif file_extension == '.py':
        run_package = await handle_py(message, file_path)
    else:
        return

    verdict_message = await message.answer('ща попробуем')
    await check(message, verdict_message, run_package)


# async def main():
#     # logging.basicConfig(level=logging.INFO)
#     await dp.start_polling(bot)


@dp.message_handler()
async def get_task_number(message: types.Message):
    global wait_for_task, test_task, ready_to_test
    if wait_for_task:
        requested = message.text
        if os.path.isdir(f'tasks/{requested}'):
            test_task = requested
            ready_to_test = True
            wait_for_task = False
            await message.answer('Well, now send me a .cpp or .py file (.txt will be considered as .cpp)')
        elif requested == '777':
            await message.answer('Never gonna give you up!')
        else:
            await message.answer('Oops, requested task not found. Send another number')


@dp.message_handler(content_types=['sticker'])
async def get_sticker(message: types.__all__):
    print(message.file_id)


if __name__ == '__main__':  # start bot
    executor.start_polling(dp, skip_updates=True)
    # asyncio.run(main())

# plans:
    # create git repository
    # documentation
    # assert .cpp or .txt
    # assert other cases
    # to test on a specified test
    # to start from the specified test
    # to add other problems, descriptions for them
    # create different generators
    # add custom generators
    # divide by single-answer and multi-answer tasks

# done:
    # send input / correct / incorrect -- as a file
    # edit message to keep in loop

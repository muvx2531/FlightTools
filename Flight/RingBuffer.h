#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include <atomic>
#include <array>
#include <cstddef>

/**
 * @brief Lock-free Single Producer Single Consumer (SPSC) ring buffer
 * 
 * High-performance circular buffer optimized for one producer thread and one consumer thread.
 * Uses atomic operations for thread-safe access without locks.
 * 
 * Template parameters:
 * - T: Type of elements stored in the buffer
 * - Size: Buffer capacity (must be power of 2 for optimal performance)
 */
template<typename T, size_t Size>
class RingBuffer
{
    static_assert((Size & (Size - 1)) == 0, "Size must be a power of 2");
    static_assert(Size > 1, "Size must be greater than 1");

public:
    RingBuffer() : m_head(0), m_tail(0) {}

    /**
     * @brief Check if buffer is empty (consumer thread)
     */
    bool empty() const noexcept {
        return m_head.load(std::memory_order_acquire) == m_tail.load(std::memory_order_acquire);
    }

    /**
     * @brief Check if buffer is full (producer thread)
     */
    bool full() const noexcept {
        const size_t next_head = (m_head.load(std::memory_order_relaxed) + 1) & (Size - 1);
        return next_head == m_tail.load(std::memory_order_acquire);
    }

    /**
     * @brief Get current number of elements in buffer
     */
    size_t size() const noexcept {
        const size_t head = m_head.load(std::memory_order_acquire);
        const size_t tail = m_tail.load(std::memory_order_acquire);
        return (head - tail) & (Size - 1);
    }

    /**
     * @brief Get buffer capacity
     */
    static constexpr size_t capacity() noexcept {
        return Size - 1;  // One slot is always kept empty to distinguish full from empty
    }

    /**
     * @brief Get buffer usage as percentage (0.0 to 1.0)
     */
    double usage() const noexcept {
        return static_cast<double>(size()) / capacity();
    }

    /**
     * @brief Push element to buffer (producer thread only)
     * @param item Element to push
     * @return true if successful, false if buffer is full
     */
    bool push(const T& item) noexcept {
        const size_t head = m_head.load(std::memory_order_relaxed);
        const size_t next_head = (head + 1) & (Size - 1);
        
        if (next_head == m_tail.load(std::memory_order_acquire)) {
            return false;  // Buffer is full
        }
        
        m_buffer[head] = item;
        m_head.store(next_head, std::memory_order_release);
        return true;
    }

    /**
     * @brief Push element with move semantics (producer thread only)
     */
    bool push(T&& item) noexcept {
        const size_t head = m_head.load(std::memory_order_relaxed);
        const size_t next_head = (head + 1) & (Size - 1);
        
        if (next_head == m_tail.load(std::memory_order_acquire)) {
            return false;  // Buffer is full
        }
        
        m_buffer[head] = std::move(item);
        m_head.store(next_head, std::memory_order_release);
        return true;
    }

    /**
     * @brief Pop element from buffer (consumer thread only)
     * @param item Reference to store the popped element
     * @return true if successful, false if buffer is empty
     */
    bool pop(T& item) noexcept {
        const size_t tail = m_tail.load(std::memory_order_relaxed);
        
        if (tail == m_head.load(std::memory_order_acquire)) {
            return false;  // Buffer is empty
        }
        
        item = m_buffer[tail];
        m_tail.store((tail + 1) & (Size - 1), std::memory_order_release);
        return true;
    }

    /**
     * @brief Pop multiple elements from buffer (consumer thread only)
     * @param items Pointer to array where elements will be stored
     * @param max_count Maximum number of elements to pop
     * @return Number of elements actually popped
     */
    size_t pop_batch(T* items, size_t max_count) noexcept {
        if (!items || max_count == 0) return 0;
        
        size_t tail = m_tail.load(std::memory_order_relaxed);
        const size_t head = m_head.load(std::memory_order_acquire);
        
        size_t available = (head - tail) & (Size - 1);
        size_t to_pop = std::min(max_count, available);
        
        for (size_t i = 0; i < to_pop; ++i) {
            items[i] = m_buffer[tail];
            tail = (tail + 1) & (Size - 1);
        }
        
        m_tail.store(tail, std::memory_order_release);
        return to_pop;
    }

    /**
     * @brief Force push element, dropping oldest if buffer is full (producer thread only)
     * This ensures the producer never blocks but may lose old data
     */
    void force_push(const T& item) noexcept {
        const size_t head = m_head.load(std::memory_order_relaxed);
        const size_t next_head = (head + 1) & (Size - 1);
        
        if (next_head == m_tail.load(std::memory_order_acquire)) {
            // Buffer is full, drop oldest half
            drop_oldest_half();
        }
        
        m_buffer[head] = item;
        m_head.store(next_head, std::memory_order_release);
    }

    /**
     * @brief Drop oldest half of the buffer to make room (consumer thread only)
     * Called automatically by force_push when buffer overflows
     */
    void drop_oldest_half() noexcept {
        const size_t current_size = size();
        const size_t drop_count = current_size / 2;
        
        if (drop_count > 0) {
            const size_t tail = m_tail.load(std::memory_order_relaxed);
            const size_t new_tail = (tail + drop_count) & (Size - 1);
            m_tail.store(new_tail, std::memory_order_release);
        }
    }

    /**
     * @brief Clear all elements from buffer (consumer thread only)
     */
    void clear() noexcept {
        m_tail.store(m_head.load(std::memory_order_acquire), std::memory_order_release);
    }

private:
    std::array<T, Size> m_buffer;
    std::atomic<size_t> m_head{0};  // Producer writes here
    std::atomic<size_t> m_tail{0};  // Consumer reads from here
};

#endif // RINGBUFFER_H